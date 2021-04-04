#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void show_type(unsigned char d_type, int depth){
	switch (d_type){
		case DT_BLK:
			printf("[block device]\n");
			break;
		case DT_CHR:
			printf("[character device]\n");
			break;
		case DT_DIR:
			printf("[directory]\n");
			break;
		case DT_FIFO:
			printf("[named pipe]");
			break;
		case DT_LNK:
			printf("[link file]");
			break;
		case DT_REG:
			printf("[regular file]\n");
			break;
		case DT_SOCK:
			printf("[sock file]");
			break;
		case DT_UNKNOWN:
			printf("[unknown file]\n");
			break;
		default:
			printf("[default file]\n");
			break;
	}
	return 0;
}


void show_dir_info(char *dir, int depth){
	DIR *pdir;
	struct dirent *dirent;

	pdir = opendir(dir);
	if(pdir == NULL){
		printf("Can not open directory:%s\n",dir);
	}

	chdir(dir);

	while((dirent = readdir(pdir)) != NULL){

		if(strcmp(dirent->d_name,".")==0||strcmp(dirent->d_name,"..")==0){
			continue;
		}

		printf("%*s|--> %s :: ",depth,"",dirent->d_name);
		show_type(dirent->d_type,depth);

		if(dirent->d_type == DT_DIR)
			show_dir_info(dirent->d_name, depth + 4);
	}

	closedir(pdir);
	chdir("..");
}

int main (int argc, char **argv){

	if(argc < 2){
		printf("usage:%s dir\n",argv[0]);
		return 0;
	}

	show_dir_info(argv[1],0);
	return 0;
}