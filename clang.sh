export OLDPROMPT="$PS1"
export PS1="(dev) $OLDPROMPT"

#架构体系
export ARCH=arm64

#目录
export DIR=~/android_xiaomi_kernel_grus

#目录变量
export IMG=Image.gz
export BUILD_DIR=${DIR}/out
export NEW_CONFIG=${DIR}/grus_defconfig
export CONFIG_DIR=${DIR}/arch/arm64/configs
export IMG_DIR=${BUILD_DIR}/arch/arm64/boot
export Watermelon=/home/gah0/Watermelon\(Q\)-9SE
#编译使用的变量
export DTPY=~/toolchain/mkdtimg/mkdtboimg.py
export CROSS_COMPILE=~/toolchain/candy/bin/aarch64-linux-gnu-
export CC=~/toolchain/candy/bin/clang
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-gnueabi-

export defconfig=grus_defconfig

#生成新的defconfig，并放入config中
mkmenu(){
  make $defconfig
  make menuconfig
  
#  if [ $? -eq 1 ]; then
#    if [ ! -f "${NEW_CONFIG}" ]; then
#      mv $NEW_CONFIG $CONFIG_DIR
}

pack(){
    echo "now creating kernel flashing.zip"
    echo "修改versionCode时间"
    sed -i -e '4cversionCode='"$(date +'%m%d')"'+beta' magisk_module/module.prop
    echo "修改kernelver时间"
		sed -i -e '4ckernelver="'$(date +'%Y%m%d')'"' kernel.conf
		zip -r Watermelon\(Q\)-9SE-$(date +'%Y%m%d').zip *
		mv Watermelon\(Q\)-9SE-$(date +'%Y%m%d').zip ..
		echo "成功生成zip卡刷包，当前时间为" + $(date +'%Y%m%d-%H:%M:%S')
    cd ${DIR}
}

move(){
	if [ -d "${Watermelon}" ]; then
		cd ${Watermelon}
  		cp ${IMG_DIR}/${IMG} ${Watermelon}
  		cp ${BUILD_DIR}/dtbo.img ${Watermelon}
  	fi
}

mke(){
	mkdir -p $BUILD_DIR
	make O=out CC=$CC CLANG_TRIPLE=$CLANG_TRIPLE $defconfig
	make O=out -j8 CC=$CC CROSS_COMPILE_ARM32=arm-linux-gnueabi- CLANG_TRIPLE=$CLANG_TRIPLE 2>&1 $@ | tee kernel.log
	test -z "$@" && mkedtimg
	move
	pack
}

mkedtimg(){
  DTOUT=/home/gah0/android_xiaomi_kernel_grus/out/dtbo.img
  MKDT=$(which $DTPY)
  if [[ -n "$MKDT" ]];then
    python2 $MKDT \
      create $DTOUT \
      $(find ${BUILD_DIR}/arch/arm64/boot/dts/qcom -iname '*-overlay.dtbo' -print)
    echo "Build dtbo.img done: $DTOUT"
  fi
}

strip(){
  ${CROSS_COMPILE}strip --strip-debug find . -name '*.ko'
  mv find . -name '*.ko' ${DIR}/today
}

mr(){
  make mrproper
  cd $BUILD_DIR
}

deactivate(){
  export PS1="$OLDPROMPT"
}

#如果你使用ZSH，带git插件。则不需要这些
gc(){
  git cherry-pick $@
}


gfh(){
  git fetch $@
}

merge(){
  git merge -s ours --no-commit --allow-unrelated-histories FETCH_HEAD
}

push(){
  #git push remote current branch
  if [ $# = 1 ]; then
    Current_branch = $1
    git push origin ${Current_branch}
  else if [ $# = 0 ]; then 
    Current_branch=`git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3`
    git push origin ${Current_branch}
  else
    Current_branch=`git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3`
    echo "无法识别当前参数，要不敲下gp试试上传当前分支: " + ${Current_branch}
  fi
}


convert_hex_2_dts(){
for i in $(ls -l |grep "device");
    do
        dtc -I dtb -O dts -o ${i}.dts ${i}
    done
}

dl_toolchain(){
		a_ARCH=$(uname -m)
		
		gcc_html_path="https://releases.linaro.org/components/toolchain/binaries/5.4-2017.05/aarch64-linux-gnu/"
		gcc_filename_prefix="gcc-linaro-5.4.1-2017.05-x86_64_aarch64-linux-gnu"
		gcc_banner="aarch64-linux-gnu-gcc (Linaro GCC 5.4-2017.05) 5.4.1"
		gcc_copyright="2015"
		datestamp="2017.05-gcc-aarch64-linux-gnu"
		
		binary="bin/aarch64-linux-gnu-"
		
		WGET="wget -c --directory-prefix=${BUILD_DIR}/"
		if [ ! -f "${gcc_dir}/${gcc_filename_prefix}/${datestamp}" ] ; then
			echo "Installing Toolchain: gcc_linaro_aarch64_gnu_5"
			echo "-----------------------------"
			${WGET} "${gcc_html_path}${gcc_filename_prefix}.tar.xz"
			tar -xf "${gcc_filename_prefix}.tar.xz" -C "${BUILD_DIR}/"
			#if [ -f "${BUILD_DIR}/${gcc_filename_prefix}/${binary}gcc" ] ; then
			#	touch "${gcc_dir}/${gcc_filename_prefix}/${datestamp}"
			#fi
		else
			echo "Using Existing Toolchain: gcc_linaro_aarch64_gnu_5"
		fi
			
		#
		#https://releases.linaro.org/components/toolchain/binaries/5.4-2017.05/aarch64-linux-gnu/gcc-linaro-5.4.1-2017.05-x86_64_aarch64-linux-gnu.tar.xz
		#https://releases.linaro.org/components/toolchain/binaries/5.5-2017.10/aarch64-linux-gnu/gcc-linaro-5.5.0-2017.10-x86_64_aarch64-linux-gnu.tar.xz
		#
}
