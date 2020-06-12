CLASH_DIR=~/programfiles/clash
WGET_LINK=\&log-level=info
RJ_PATH=~/programfiles/rjsupplicant
RUIJIE_USER=123456
PASSWD=987654

login(){
  cd ${RJ_PATH}
  sudo ./rjsupplicant.sh -d 1 -n enx00e04a37770b -u ${RUIJIE_USER} -p ${PASSWD} 
  sudo service network-manager start
  w3m 2.2.2.2
}

update(){
  cd ${CLASH_DIR} 
  wget -O config.yml ${WGET_LINK} 2>&1 | tee tmp.log

	if [ $? -ne 0 ] ;then
      if [ $(cat tmp.log | grep "failed") -eq 1 ]; then
          echo "failed to create config.yml"
          return 0
      fi
   		echo "no reason failed"
	else
      if [ $(cat tmp.log | grep "Connection refuse") ]; then
          unset HTTP_PROXY
          unset http_proxy
          unset HTTPS_PROXY
          unset https_proxy
          unset ALL_PROXY
          update
      fi
  fi

  if test -f 'config.yml' ;then
      if test -s config.yml ;then
          mv config.yml config.yaml
      else
          echo "config.yml is empty"
          update
      fi
	fi 
}

clash(){
  cd ${CLASH_DIR} 
  $ ./clash -d . 

  if test $? -eq 0 ;then
      echo "success"
  fi

	if [ dpkg -l | grep w3m ];then
    	if [ $? -eq 0 ];then
      		#选择延迟短的线路：正在实现
      		w3m http://clash.razord.top/#/proxiesw
    	else
      		sudo apt install w3m
    	fi
	fi

  if [ $(env|grep -c "PROXY") -ne 3 ];then
      export HTTPS_PROXY=http://127.0.0.1:23456/
      export ALL_PROXY=socks://127.0.0.1:23456/
      export HTTP_PROXY=http://127.0.0.1:23456/
  fi
}