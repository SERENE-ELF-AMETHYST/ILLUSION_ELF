#ifndef __PLUGIN_H__
#define __PLUGIN_H__
/*
*插件父类
*/

#include<iostream>
namespace ASE
{
	class PlugIn
	{
	public:
		enum ASE_PLUGIN_TYPE { ASE_PLUGIN_GLOBAL,ASE_PLUGIN_COMMAND};
	public:
		PlugIn();
		virtual bool	Run() = 0;
		std::string		GetName();
		ASE_PLUGIN_TYPE GetType();
		bool			GetStatus();
		~PlugIn();
	protected:
		bool			isRun;	//是否运行
		std::string		mName;	//插件名称
		ASE_PLUGIN_TYPE mType;	//插件类型
		
	};
}
#endif // !__PLUGIN_H__


