#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "include/tpl.h"
#include "include/common.h"

void debug(const char* format,...){
	if (DEBUG_ON){
		va_list args;
		fprintf(stderr, "[DEBUG]: ");
		va_start (args, format);
		vfprintf(stderr, format, args);
		va_end(args);
		fprintf(stderr, "\n");
	}
}


void perrorf(const char* format,...){
	int en = errno;
	va_list args;
	fprintf(stderr, "[DEBUG]: ");
	va_start (args, format);
	vfprintf(stderr, format, args);
	va_end(args);

	fprintf(stderr, " : %s\n", strerror(en));

}

int arg_command_serialize(char **buf, int *len, const struct arg_command* cmd){
	tpl_node *tn;
	//debug("size %d", cmd->argc);
	//return 0;

	tn = tpl_map("s#", cmd->argv, cmd->argc);
	tpl_pack(tn, 0);

	int size;
	char* buffer; 
	tpl_dump(tn, TPL_MEM, &buffer, &size);
	debug("size%d", size);
	tpl_free(tn);
	*len = sizeof(cmd->argc)+size;

	(*buf) = (char *)malloc(*len);
	//debug("len: %d", *len);
	memcpy((*buf), &cmd->argc, sizeof(cmd->argc));
	//memset(&((*buf)[sizeof(cmd->argc)]), 1, *len);
	memcpy(&((*buf)[sizeof(cmd->argc)]), buffer, size);
	free(buffer);
	// int i = 0;
	// for (i = 0; i<*len; i++){
	// 	printf("%d\n",(*buf)[i]);
	// 	fflush(stdout);
	// }
	return 0;

}


int arg_command_deserialize(struct arg_command *cmd, const char *buf, int len){
	int32_t argc=0;

	memcpy(&argc, buf, sizeof(argc));
	tpl_node *tn;
	char * argv[argc];
	tn = tpl_map("s#", &argv, argc);

	tpl_load(tn, TPL_MEM, &buf[sizeof(argc)], len-sizeof(argc));
	tpl_unpack(tn,0);
	tpl_free(tn);
	int i;
	fflush(stdout);
	cmd->argc = argc;
	cmd->argv = (char**) malloc(argc * sizeof(char*));
	for (i = 0; i<argc; i++){
		cmd->argv[i]= argv[i];
	}



	return 0;
}

int con_info_serialize(char **buf, int *len, const struct con_info_type *con_info){
	tpl_node *tn;
	tn = tpl_map("S($(uvuv)u)", con_info);
	tpl_pack(tn, 0);
	tpl_dump(tn, TPL_MEM, buf, len);
	tpl_free(tn);
	return 0;
}



int con_info_deserialize(struct con_info_type *con_info, const char *buf, int len){
	//debug("deserialize called, len: %d", len);
	tpl_node *tn;
	tn = tpl_map("S($(uvuv)u)", con_info);
	tpl_load(tn, TPL_MEM, buf, len);
	tpl_unpack(tn, 0);
	tpl_free(tn);
	return 0;
}