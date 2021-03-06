/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../util.h"

#if defined(__linux__)
	const char *
	cpu_freq(void)
	{
		int freq;

		return (pscanf("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq",
		               "%i", &freq) == 1) ?
		       bprintf("%d", (freq + 500) / 1000) : NULL;
	}

	const char *
	cpu_perc(void)
	{
		int perc;
		static long double a[7] = {0};
		static int valid;
		long double b[7];

		memcpy(b, a, sizeof(b));
		//Format user, nice, system, idle, iowait, irq, softirq
		if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
		           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]) != 7) {
			return NULL;
		}
		if (!valid) {
			valid = 1;
			return NULL;
		}

		long double usedCPU1 = (a[0] + a[1] + a[2] + a[5] + a[6]);
		long double usedCPU2 = (b[0] + b[1] + b[2] + b[5] + b[6]);
		long double usedCPUDelta = usedCPU1 - usedCPU2;

		long double totalCPU1 = 0;
		long double totalCPU2 = 0;

		for (unsigned char i = 0; i < 7; i++)
		{
			totalCPU1 += a[i];
			totalCPU2 += b[i];
		}

		long double totalCPUDelta = totalCPU1 - totalCPU2;

		perc = 10000.0 * (usedCPUDelta / totalCPUDelta);
		

		return bprintf("%*.3g", 4, (perc / 100.f));
	}

	const char *
	cpu_iowait(void)
	{
		int perc;
		static int valid;
		static long double a[7];
		long double b[7];

		memcpy(b, a, sizeof(b));
		if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
		           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]) != 7) {
			return NULL;
		}
		if (!valid) {
			valid = 1;
			return NULL;
		}

		perc = 100 * ((b[4]) - (a[4])) /
		       ((b[0]+b[1]+b[2]+b[3]+b[4]+b[5]+b[6]) -
		        (a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]));

		return bprintf("%d", perc);
	}
#elif defined(__OpenBSD__)
	#include <sys/sysctl.h>

	const char *
	cpu_freq(void)
	{
		int freq, mib[2];
		size_t size;

		mib[0] = CTL_HW;
		mib[1] = HW_CPUSPEED;

		size = sizeof(freq);

		if (sysctl(mib, 2, &freq, &size, NULL, 0) == -1) {
			fprintf(stderr, "sysctl 'HW_CPUSPEED': %s\n",
			        strerror(errno));
			return NULL;
		}

		return bprintf("%d", freq);
	}
#endif
