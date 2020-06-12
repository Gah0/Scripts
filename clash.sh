CLASH_DIR=~/home/gah0/programfiles/clash
wget_link=\&

update(){
  	cd CLASH_DIR
  	[ wget -O config.yml ${wget_link} ]

	if [ -f 'config.yml' ] ;then
		mv config.yml config.yaml
	fi

	if [ $? -ne 0 ] ;then
   		echo "failed to mv config.yml"
	else
		echo "更新config.yaml成功！"
	fi 
}

clash(){
  cd $CLASH_DIR 
  $ ./clash -d . > tmpfile.log
	if [ cat tmpfile.log | grep "listening at :2345" -eq 1 ];then
		echo "success"
	fi

	if [ dpkg -l | grep w3m ];then
    	if [ $? -eq 0 ];then
      		#选择延迟短的线路：正在实现
      		w3m http://clash.razord.top/#/proxiesw
    	else
      		sudo apt install w3m
    	fi

    	if [ $(env|grep -c "PROXY") -ne 3 ];then
      		export HTTPS_PROXY=http://127.0.0.1:2345/
      		export ALL_PROXY=socks://127.0.0.1:2345/
      		export HTTP_PROXY=http://127.0.0.1:2345/
    	fi
	fi
}