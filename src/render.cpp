#include "../inc/Processor.class.hpp"
#include "../inc/Host.class.hpp"
#include "../inc/ft_gkrellm.hpp"
#include <stdio.h>
#include <unistd.h>
#include <mach/mach_host.h>
#include <mach/processor_info.h>
#include <iostream>
# include <sys/sysctl.h>
# include <netinet/in.h>
# include <net/if.h>
# include <net/route.h>
# include <list>

typedef struct AvgBps {
	double rate_;            // The average rate
	double last_;            // Accumulates bytes added until average is computed
	time_t prev_;            // Time of previous update
	AvgBps () : rate_(0), last_(0), prev_(time(0)) {}
	void add (unsigned bytes) {
		time_t now = time(0);
		if (now - prev_ < 60) {       // The update is within the last minute
			last_ += bytes;           // Accumulate bytes into last
			if (now > prev_) {        // More than a second elapsed from previous
				// exponential moving average
				// the more time that has elapsed between updates, the more
				// weight is assigned for the accumulated bytes
				double alpha = (now - prev_)/60.0;
				rate_ = alpha * last_ + (1 - alpha) * rate_;
				last_ = 0;            // Reset last_ (it has been averaged in)
				prev_ = now;          // Update prev_ to current time
			}
		} else {                      // The update is longer than a minute ago
			rate_ = bytes;            // Current update is average rate
			last_ = 0;                // Reset last_
			prev_ = now;              // Update prev_
		}
	}
	double rate () {
		add(0);                       // Compute rate by doing an update of 0 bytes
		return rate_;                 // Return computed rate
	}
} t_a;
void	separation(void)
{
	attron(COLOR_PAIR(1));
	printw("\n-------------------------\n\n");
	attroff(COLOR_PAIR(1));
}

static double ParseMemValue(const char * b)
{
	while((*b)&&(std::isdigit(*b) == false))
		b++;
	return std::isdigit(*b) ? atof(b) : -1.0;
}

float	ft_canoe(void)
{
	FILE *          fpIn = popen("/usr/bin/vm_stat", "r");
	double          val;
	double          pagesUsed;
	double          totalPages;
	char            buf[0xF00];

	if (fpIn)
	{
		pagesUsed = 0.0;
		totalPages = 0.0;
		while(fgets(buf, sizeof(buf), fpIn) != NULL)
		{
			if (strncmp(buf, "Pages", 5) == 0)
			{
				val = ParseMemValue(buf);
				if (val >= 0.0)
				{
					if ((strncmp(buf, "Pages wired", 11) == 0)||(strncmp(buf, "Pages active", 12) == 0))
						pagesUsed += val;
					totalPages += val;
				}
			}
			else if (strncmp(buf, "Mach Virtual Memory Statistics", 30) != 0)
				break;
		}
		pclose(fpIn);

		if (totalPages > 0.0)
			return (static_cast<float>((pagesUsed / totalPages) * 100.0f));
	}
	return -1.0f;
}


class CpuUsage {
	public:
		CpuUsage(int core): core_(core) {
//   Updated: 2015/11/18 16:38:10 by gfournie         ###   ########.fr       //
		}

		float get() {
			Ticks t = updated_ticks_(core_);
			unsigned long long int used = t.used() - prev.used();
			unsigned long long int total = t.total() - prev.total();
			prev = t;
			return static_cast<float>(used) / static_cast<float>(total) * 100.0f;
		}

	private:
		struct Ticks {
			unsigned long long int usertime;
			unsigned long long int nicetime;
			unsigned long long int systemtime;
			unsigned long long int idletime;

			unsigned long long int used() { return usertime + nicetime + systemtime; }
			unsigned long long int total() { return usertime + nicetime + systemtime + idletime; }
		} prev;

		int core_;

		Ticks updated_ticks_(int core) {
			unsigned int cpu_count;
			processor_cpu_load_info_t cpu_load;
			mach_msg_type_number_t cpu_msg_count;

			int rc =  host_processor_info(
					mach_host_self( ),
					PROCESSOR_CPU_LOAD_INFO,
					&cpu_count,
					(processor_info_array_t *) &cpu_load,
					&cpu_msg_count
					);
			if (rc != 0) {
				printf("Error: failed to scan processor info (rc=%d)\n", rc);
				exit(1);
			}

			if (core < 0 || static_cast<int>(cpu_count) <= core) {
				printf("Error: invalid core number: %d\n", core);
				exit(1);
			}
			unsigned long long int usertime = cpu_load[core].cpu_ticks[CPU_STATE_USER];
			unsigned long long int nicetime = cpu_load[core].cpu_ticks[CPU_STATE_NICE];
			unsigned long long int systemtime = cpu_load[core].cpu_ticks[CPU_STATE_SYSTEM];
			unsigned long long int idletime = cpu_load[core].cpu_ticks[CPU_STATE_IDLE];

			Ticks t = {usertime, nicetime, systemtime, idletime};
			return t;
		}

};

CpuUsage a(0), b(1), c(2), d(3);
	
void marator()
{
	int			mib[] = { CTL_NET, PF_ROUTE, 0, 0, NET_RT_IFLIST2, 0 };
	char        *lim;
	char        *next;
	uint64_t    totalibytes;
	uint64_t    totalobytes;
	size_t      len;
	char        buf[0xF00] = {0};

	totalibytes = 0;
	totalobytes = 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
	   return ;
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0)
	   return ;
	lim = buf + len;
	for (next = buf; next < lim; )
	{
		struct if_msghdr *ifm = (struct if_msghdr*)next;
		next += ifm->ifm_msglen;
		if (ifm->ifm_type == RTM_IFINFO2)
		{
			struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;
			totalibytes += if2m->ifm_data.ifi_ibytes;
			totalobytes += if2m->ifm_data.ifi_obytes;
		}
	}
	printw("output: %f input  %f\n",totalobytes , totalibytes);
}

void	req_render(void)
{
	static std::time_t prev_time = std::time(NULL) - 1;
	std::time_t cur_time;

	if (!((cur_time = std::time(NULL)) >= (prev_time + 1)))
		return ;
	prev_time = cur_time;
	render();
}

void	render(void)
{
	std::time_t cur_time = std::time(NULL);
	static Processor proc;
	static Host host;

	clear();

	printw("Time: %s", std::asctime(std::localtime(&cur_time)));
	separation();
	printw("Hostname: %s\n", host.getHostName().c_str());
	printw("Username: %s\n", host.getUserName().c_str());
	separation();
	printw("Processor name: %s\n", proc.getProcessorName().c_str());
	printw("Processor model: %s\n", proc.getProcessorModel().c_str());
	printw("Core number: %d\n", proc.getCoreNumber());
	printw("Active core number: %d\n", proc.getActiveCoreNumber());
	printw("Core Activity: %6.2lf, %6.2lf, %6.2lf, %6.2lf\n", a.get(), b.get(), c.get(), d.get());
	separation();
	printw("RAM usage: %f/100%%\n", ft_canoe());
	separation();
//	marator();
	//printw("%lf\n", e.rate());
	refresh();
}

void	controller(void)
{
	static int	key = 0;

	key = getch();
	switch (key) {
	case 'q':
	case 'Q':
		end_term();
		exit(0);
	}
	key = 0;
}

void processation(t_env & e)
{
	int i = 39;
	while (--i > -1)
		e.tab[i + 1] = e.tab[i];
	e.tab[0] = (a.get()) * 2;
	i = 40;
	int x = 100; 
	while (--i > -1)
	{
		bar(e.tab[i], x, 500, e);
		x += 5;
	}
	i = 39;
	while (--i > -1)
		e.tab2[i + 1] = e.tab2[i];
	e.tab2[0] = (b.get()) * 2;
	i = 40;
	x = 320;
	while (--i > -1)
	{
		bar(e.tab2[i], x, 500, e);
		x += 5;
	}
	i = 39;
	while (--i > -1)
		e.tab3[i + 1] = e.tab3[i];
	e.tab3[0] = (c.get()) * 2;
	i = 40;
	x = 540;
	while (--i > -1)
	{
		bar(e.tab3[i], x, 500, e);
		x += 5;
	}
	i = 39;
    while (--i > -1)
		e.tab4[i + 1] = e.tab4[i];
    e.tab4[0] = (d.get()) * 2;
    i = 40;
    x = 760;
    while (--i > -1)
    {
        bar(e.tab4[i], x, 500, e);
        x += 5;
	}
	i = 79;
    while (--i > -1)
        e.tab5[i + 1] = e.tab5[i];
    e.tab5[0] = (ft_canoe()) * 2;
    i = 80;
    x = 760;
    while (--i > -1)
    {
        bar(e.tab5[i], x, 250, e);
        x += 5;
    }
}

void    render2(t_env & e)
{
	std::time_t cur_time = std::time(NULL);
    static Processor proc;
    static Host host;
	char  s[0xF00];


	processation(e);
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	sprintf(s, "Time: %s", std::asctime(std::localtime(&cur_time)));
	mlx_string_put(e.mlx, e.win, 80, 20, 0x777777, s);
	sprintf(s,"Hostname: %s\n", host.getHostName().c_str());
	mlx_string_put(e.mlx, e.win, 80, 40, 0x777777, s);
	sprintf(s,"Username: %s\n", host.getUserName().c_str());
	mlx_string_put(e.mlx, e.win, 80, 60, 0x777777, s);
	sprintf(s, " Processor name: %s Processor model: %s\n", proc.getProcessorName().c_str(), proc.getProcessorModel().c_str());
	mlx_string_put(e.mlx, e.win, 80, 510, 0x777777, s);
	sprintf (s, "Core number: %d Active core number: %d", proc.getCoreNumber(), proc.getActiveCoreNumber());
	mlx_string_put(e.mlx, e.win, 120, 525, 0x777777, s);
	sprintf(s,"Core Activity\n");
	mlx_string_put(e.mlx, e.win, 80, 270, 0x777777, s);
	sprintf(s,"RAM usage: %f/100%%\n", ft_canoe());
	mlx_string_put(e.mlx, e.win, 800, 20, 0x777777, s);
//    separation();
//  marator();
    //printw("%lf\n", e.rate());
//    refresh();

}
