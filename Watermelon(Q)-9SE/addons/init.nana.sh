#!/system/bin/sh

trap 'nukeself $?' EXIT
selfpath=$(realpath $0)

kwrite(){
  echo $1 2>&1 >/dev/kmsg;
}

write(){
  echo $2 > $1
  [[ "$?" == "1" ]] && { kwrite "Gah0: failed to set $1 to $2"; }
}

nukeself(){
  if [[ "$1" == "5" ]];then
    kwrite "Gah0: launching self-destroy mechanism"
    grep 'nukeself' $selfpath 2>&1 /dev/null && rm "$selfpath"
  fi
}

if ! grep 'Watermelon' /proc/sys/kernel/osrelease 2>&1 /dev/null; then
  kwrite "Gah0: unknown kernel, exit with crying."
  exit 5
fi

# Hax sepolicy for broken custom ROM
magiskpolicy --live "allow * vendor_camera_prop file { read open getattr map }"
magiskpolicy --live "allow * camera_prop file { read open getattr map }"
magiskpolicy --live "allow * hal_fingerprint_hwservice hwservice_manager { find }"

# wait until boot is complete
while true; do 
  if [[ "$(getprop sys.boot_completed)" == "1" ]]; then
    break
  else
    sleep 1
  fi
done

sleep 3

# Disable MIUI AD
miui=`getprop ro.miui.notch`
if [ "$miui" == "1" ]; then
rm -rf /data/media/0/miad
echo "" > /data/media/0/miad
fi

# Cluster
cpuA=/sys/devices/system/cpu/cpufreq/policy0
cpuB=/sys/devices/system/cpu/cpufreq/policy6

write $cpuA/scaling_min_freq 576000
write $cpuA/scaling_governor schedutil
write $cpuA/schedutil/iowait_boost_enable 0
write $cpuA/schedutil/up_rate_limit_us 500
write $cpuA/schedutil/down_rate_limit_us 1000
write $cpuB/scaling_governor schedutil
write $cpuA/scaling_min_freq 300000
write $cpuB/schedutil/iowait_boost_enable 0
write $cpuB/schedutil/up_rate_limit_us 2000
write $cpuB/schedutil/down_rate_limit_us 1000

# Enable idle state listener
write /sys/class/drm/card0/device/idle_encoder_mask 1
write /sys/class/drm/card0/device/idle_timeout_ms 64

#IO Scheduler
# Unify all blocks setup
for i in /sys/block/*/queue; do
  write $i/read_ahead_kb 2048
  write $i/add_random 0
  write $i/iostats 0
  write $i/rotational 0
  write $i/scheduler maple
done

#GPU
write $/sys/class/kgsl/kgsl-3d0/devfreq/min_freq 180000000
write $/sys/class/kgsl/kgsl-3d0/min_gpuclk 180000000
write $/sys/class/kgsl/kgsl-3d0/devfreq/max_freq 610000000
write $/sys/class/kgsl/kgsl-3d0/max_gpuclk 610000000
write $/sys/class/kgsl/kgsl-3d0/throttling 0

#LMK
# echo "18432,23040,27648,32256,85296,120640" > /sys/module/lowmemorykiller/parameters/minfree

# TCP Congestion
write /proc/sys/net/ipv4/tcp_congestion_control bbr