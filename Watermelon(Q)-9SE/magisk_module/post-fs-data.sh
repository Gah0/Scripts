#!/system/bin/sh
MODDIR=${0%/*}

# Cluster
cpuA=/sys/devices/system/cpu/cpufreq/policy0
cpuB=/sys/devices/system/cpu/cpufreq/policy6

echo "576000" > cpuA/scaling_min_freq
echo "schedutil" > $cpuA/scaling_governor 
echo "0" > cpuA/schedutil/iowait_boost_enable
#write $cpuA/schedutil/up_rate_limit_us 500
#write $cpuA/schedutil/down_rate_limit_us 1000
echo "300000" > cpuB/scaling_min_freq
echo "schedutil" > cpuB/scaling_governor 
echo "0" > cpuB/schedutil/iowait_boost_enable
#write $cpuB/schedutil/up_rate_limit_us 2000
#write $cpuB/schedutil/down_rate_limit_us 1000

# Enable idle state listener
echo "1" > /sys/class/drm/card0/device/idle_encoder_mask
echo "64" > /sys/class/drm/card0/device/idle_timeout_ms

#IO Scheduler
# Unify all blocks setup
for i in /sys/block/*/queue; do
  echo "2048" > i/read_ahead_kb
  echo "0" > i/add_random
  echo "0" >i/iostats
  echo "0" >i/rotational
  echo "maple" >i/scheduler
done

#GPU
echo  "180000000" > /sys/class/kgsl/kgsl-3d0/devfreq/min_freq
echo  "180000000" > /sys/class/kgsl/kgsl-3d0/min_gpuclk 
echo  "610000000" > /sys/class/kgsl/kgsl-3d0/devfreq/max_freq
echo  "610000000" > /sys/class/kgsl/kgsl-3d0/max_gpuclk
# write $/sys/class/kgsl/kgsl-3d0/throttling 0

#LMK
# echo "18432,23040,27648,32256,85296,120640" > /sys/module/lowmemorykiller/parameters/minfree

# TCP Congestion
echo "bbr" > /proc/sys/net/ipv4/tcp_congestion_control