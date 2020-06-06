CLASH_DIR=~/home/gah0/programfiles/clash
http-p=

update(){
  cd CLASH_DIR
  [ wget -O config.yml http ]

  if [ -f 'config.yml' ] ;then
	   mv config.yml config.yaml

  if [ $? -ne 0 ] ;then
	echo "failed to mv config.yml"
  else
	echo "更新config.yaml成功！"
	}

clash(){
	[ ./clash -d . ]

	if [ dpkg -l | grep w3m ];then
   		if [ $? -eq 0 ];then
     			w3m http://clash.razord.top/#/proxiesw
   		else
	    		sudo apt install w3m
	  	fi
 	fi
}