#include <stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	bool install=false;
	bool debug=false;
	if(strcmp(argv[0],"byd") == 0)install=true;
	if(argc >= 2)for(int i=1;i<argc;i++)if(strcmp(argv[i],"debug") == 0)debug=true;
//---------------------------------
	if(debug)
	{
		printf("参数数量:%d\n",argc-1);
		printf("具体参数");
		for(int i=1;i<argc;i++)
		{
			printf("%s ",argv[i]);
		}
		printf("\n");
		printf("path:%s\n",argv[0]);
	}
//----------------------------------
	if(argc <= 1 || strcmp(argv[1],"help") == 0 || strcmp(argv[1],"帮助") == 0)
	{
		printf("帮助：\n");
		if(!install)printf("installbyd 或 安装byd    安装byd命令到系统\n");
		if(install)printf("uninstallbyd 或 卸载byd  从系统卸载byd\n");
		printf("install 或 安装          安装一个软件源软件包\n");
		printf("bydfile 或 安装byd包     byd包安装本地.byd软件包组\n");
		printf("update 或 刷新           刷新软件源\n");
		printf("upgrade 或 更新          更新软件包\n");
		printf("upbyd 或 更新byd         更新软件包\n");
		printf("remove 或 删除           删除软件包\n");
		printf("	带参数 purge 或 删配置 以完全删除软件包\n");
		printf("autoremove 或 删除无用包           删除软件包\n");
                printf("        带参数 purge 或 删配置 以完全删除软件包\n");
		printf("版本V1.4.1\n");
	}
	else if(strcmp(argv[1],"installbyd") == 0 || strcmp(argv[1],"安装byd") == 0)
	{
	        char cmd[256]="sudo mv ";
	        strcat(cmd,argv[0]);
	        strcat(cmd," /usr/local/bin/byd");
	        system(cmd);
	        printf("byd已被安装到您的系统，您现在可以使用“byd”命令来调用\n");
	}
	else if(strcmp(argv[1],"uninstallbyd") == 0 || strcmp(argv[1],"卸载byd") == 0)
	{
	        system("sudo rm /usr/local/bin/byd");
	        printf("已卸载byd\n");
	}
	else if(strcmp(argv[1],"install") == 0 || strcmp(argv[1],"安装") == 0)
	{
	        char name[256]="";
		if(argc >= 3)strcat(name,argv[2]);
		else
		{
			printf("你要安装软件包的名字：");
			scanf("%s",name);
	        }
		char cmd[256]="sudo apt install ";
		strcat(cmd,name);
		int status = system(cmd);
		if(debug){printf("返回码：%d\n",WEXITSTATUS(status));printf("name:%s\n",name);}
		if(WEXITSTATUS(status) == 100)
		{
		        printf("找不到这个软件包欸，要帮你搜一下吗？[y/n]\n");
		        char in[256];
		        scanf("%s",in);
		        char find[256]="apt list | grep -i ";
		        strcat(find,name);
		        if(strcasecmp(in,"y") == 0)system(find);
		        else printf("那你自己找吧，我溜了～\n");
                }
	}
	else if(strcmp(argv[1],"bydfile") == 0 || strcmp(argv[1],"安装byd包") == 0)
	{
	        char path[256]="";
		if(argc >= 3)strcat(path,argv[2]);
		else
		{
			printf("请输入您的byd文件路径：");
			scanf("%s",path);
	        }
		char cmd[256]="sudo unzip ";
		strcat(cmd,path);
		strcat(cmd," -d /tmp/byd");
		system("rm -rf /tmp/byd");
		system("mkdir /tmp/byd");
		system(cmd);
		system("sudo apt install /tmp/byd/*.deb");
		system("rm -rf /tmp/byd");
	}
	else if(strcmp(argv[1],"update") == 0 || strcmp(argv[1],"刷新") == 0)
	{
	        system("sudo apt update");
	}
	else if(strcmp(argv[1],"upgrade") == 0 || strcmp(argv[1],"更新") == 0)
	{
	        system("sudo apt upgrade");
	}
	else if(strcmp(argv[1],"彩蛋") == 0)
	{
	        printf("恭喜你发现了彩蛋...补兑...彩蛋怎么跑了？\n");
	        printf("找到啦，是一串数字欸：3027992723\n");
	}
	else if(strcmp(argv[1],"upbyd") == 0 || strcmp(argv[1],"更新byd") == 0)
	{
	        system("wget -P /tmp/byd/ https://raw.githubusercontent.com/abcd58758/byd/refs/heads/main/byd");
	        system("sudo mv /tmp/byd/byd /usr/local/bin/byd");
	        system("sudo chmod +x /usr/local/bin/byd");
	        printf("已尝试更新，版本见help/帮助\n");
	}
	else if(strcmp(argv[1],"remove") == 0 || strcmp(argv[1],"删除") == 0)
	{
	        bool deldata=false;
	        if(argc >= 2)for(int i=1;i<argc;i++)if(strcmp(argv[i],"purge") == 0 || strcmp(argv[i],"删配置") == 0)deldata=true;
	        char name[256]="";
		if(argc >= 3)strcat(name,argv[2]);
		else
		{
			printf("你要卸载软件包的名字：");
			scanf("%s",name);
	        }
		char cmd[256]="";
		if(deldata)strcat(cmd,"sudo apt purge ");
		else strcat(cmd,"sudo apt remove ");
		strcat(cmd,name);
		int status = system(cmd);
		if(debug)printf("执行命令：%s\n",cmd);
		if(debug){printf("返回码：%d\n",WEXITSTATUS(status));printf("name:%s\n",name);}
		if(WEXITSTATUS(status) == 100)
		{
		        printf("找不到这个软件包欸，要帮你搜一下吗？[y/n]\n");
		        char in[256];
		        scanf("%s",in);
		        char find[256]="apt list --installed | grep -i ";
		        strcat(find,name);
		        if(strcasecmp(in,"y") == 0)system(find);
		        else printf("那你自己找吧，我溜了～\n");
                }
	}
	else if(strcmp(argv[1],"autoremove") == 0 || strcmp(argv[1],"删除无用包") == 0)
	{
	        system("sudo apt upgrade");
	        bool deldata=false;
	        if(argc >= 2)for(int i=1;i<argc;i++)if(strcmp(argv[i],"purge") == 0 || strcmp(argv[i],"删配置") == 0)deldata=true;
	        if(deldata)system("sudo apt autoremove --purge");
	        else system("sudo apt autoremove");
	}
	else printf("未知命令，请输入help查看帮助\n");
	return 0;
}
