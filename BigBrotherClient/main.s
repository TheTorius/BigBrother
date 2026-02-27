	.file	"main.c"
 # GNU C17 (x86_64-posix-seh-rev0, Built by MinGW-W64 project) version 11.5.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.5.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=core2 -march=nocona -fno-asynchronous-unwind-tables -finput-charset=UTF-8 -fexec-charset=windows-1250
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
printf:
	pushq	%rbp	 #
	movq	%rsp, %rbp	 #,
	pushq	%rbx	 #
	subq	$56, %rsp	 #,
	movq	%rcx, 16(%rbp)	 # __format, __format
	movq	%rdx, 24(%rbp)	 #,
	movq	%r8, 32(%rbp)	 #,
	movq	%r9, 40(%rbp)	 #,
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	leaq	24(%rbp), %rax	 #, tmp86
	movq	%rax, -32(%rbp)	 # tmp86, MEM[(char * *)&__local_argv]
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	movq	-32(%rbp), %rbx	 # __local_argv, __local_argv.9_1
	movl	$1, %ecx	 #,
	movq	__imp___acrt_iob_func(%rip), %rax	 #, tmp87
	call	*%rax	 # tmp87
	movq	%rbx, %r8	 # __local_argv.9_1,
	movq	16(%rbp), %rdx	 # __format,
	movq	%rax, %rcx	 # _2,
	call	__mingw_vfprintf	 #
	movl	%eax, -20(%rbp)	 # tmp88, __retval
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:374:   return __retval;
	movl	-20(%rbp), %eax	 # __retval, _10
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:375: }
	movq	-8(%rbp), %rbx	 #,
	leave	
	ret	
	.def	sprintf;	.scl	3;	.type	32;	.endef
sprintf:
	pushq	%rbp	 #
	movq	%rsp, %rbp	 #,
	subq	$48, %rsp	 #,
	movq	%rcx, 16(%rbp)	 # __stream, __stream
	movq	%rdx, 24(%rbp)	 # __format, __format
	movq	%r8, 32(%rbp)	 #,
	movq	%r9, 40(%rbp)	 #,
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:399:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	leaq	32(%rbp), %rax	 #, tmp85
	movq	%rax, -16(%rbp)	 # tmp85, MEM[(char * *)&__local_argv]
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:400:   __retval = __mingw_vsprintf( __stream, __format, __local_argv );
	movq	-16(%rbp), %rdx	 # __local_argv, __local_argv.8_1
	movq	24(%rbp), %rax	 # __format, tmp86
	movq	%rdx, %r8	 # __local_argv.8_1,
	movq	%rax, %rdx	 # tmp86,
	movq	16(%rbp), %rcx	 # __stream,
	call	__mingw_vsprintf	 #
	movl	%eax, -4(%rbp)	 # tmp87, __retval
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:402:   return __retval;
	movl	-4(%rbp), %eax	 # __retval, _9
 # C:/Program Files/RedPanda-Cpp/mingw64/x86_64-w64-mingw32/include/stdio.h:403: }
	leave	
	ret	
	.globl	GLOBAL_SERVER_IP
	.data
	.align 16
GLOBAL_SERVER_IP:
	.ascii "127.0.0.1\0"
	.space 6
	.globl	MAX_WIN_COUNT
	.align 4
MAX_WIN_COUNT:
	.long	50
	.globl	PORT
	.align 4
PORT:
	.long	12345
	.globl	BLACKLIST
	.section .rdata,"dr"
.LC0:
	.ascii "chrome\0"
.LC1:
	.ascii "firefox\0"
.LC2:
	.ascii "edge\0"
.LC3:
	.ascii "opera\0"
.LC4:
	.ascii "seznam\0"
.LC5:
	.ascii "chat\0"
.LC6:
	.ascii "winscp\0"
.LC7:
	.ascii "cmd\0"
.LC8:
	.ascii "console\0"
.LC9:
	.ascii "far\0"
.LC10:
	.ascii "outlook\0"
.LC11:
	.ascii "teams\0"
.LC12:
	.ascii "kazov\0"
	.data
	.align 32
BLACKLIST:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.quad	.LC7
	.quad	.LC8
	.quad	.LC9
	.quad	.LC10
	.quad	.LC11
	.quad	.LC12
	.quad	0
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC13:
	.ascii "-port\0"
.LC14:
	.ascii "-ip\0"
.LC15:
	.ascii "-winCNT\0"
.LC16:
	.ascii "BigBrotherClient\0"
	.align 8
.LC17:
	.ascii "\12CHYBA: Nepodarilo se nastavit odchytavani zavreni okna!\12\0"
.LC18:
	.ascii "Big Brother v%.1f - %d\0"
	.align 8
.LC19:
	.ascii "Spoustim monitoring klienta (Big Brother)...\12\0"
.LC20:
	.ascii "nullptr\0"
.LC21:
	.ascii "Sledovany soubor: %s\12\0"
.LC22:
	.ascii "Server IP: %s:%d\12\0"
.LC23:
	.ascii "Verze BigBrothera: %.1f\12\0"
	.align 8
.LC24:
	.ascii "Selhala inicializace Winsock.\12\0"
.LC25:
	.ascii "pause\0"
.LC26:
	.ascii "HELLO\0"
.LC27:
	.ascii "CONFIG\0"
.LC28:
	.ascii "START\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	pushq	%rbp	 #
	movq	%rsp, %rbp	 #,
	andq	$-16, %rsp	 #,
	subq	$736, %rsp	 #,
	movl	%ecx, 16(%rbp)	 # argc, argc
	movq	%rdx, 24(%rbp)	 # argv, argv
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:24: int main(int argc, char* argv[]) {
	call	__main	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:25: 	PORT = 0;
	movl	$0, PORT(%rip)	 #, PORT
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:26: 	GLOBAL_SERVER_IP[0] = '\0';
	movb	$0, GLOBAL_SERVER_IP(%rip)	 #, GLOBAL_SERVER_IP[0]
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:27: 	MAX_WIN_COUNT = 0;
	movl	$0, MAX_WIN_COUNT(%rip)	 #, MAX_WIN_COUNT
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:29: 	for(int i = 1; i < argc; i++) {
	movl	$1, 732(%rsp)	 #, i
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:29: 	for(int i = 1; i < argc; i++) {
	jmp	.L6	 #
.L10:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:30: 		if(!strcmp(argv[i],"-port")) {
	movl	732(%rsp), %eax	 # i, tmp129
	cltq
	leaq	0(,%rax,8), %rdx	 #, _2
	movq	24(%rbp), %rax	 # argv, tmp130
	addq	%rdx, %rax	 # _2, _3
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:30: 		if(!strcmp(argv[i],"-port")) {
	movq	(%rax), %rax	 # *_3, _4
	leaq	.LC13(%rip), %rdx	 #, tmp131
	movq	%rax, %rcx	 # _4,
	call	strcmp	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:30: 		if(!strcmp(argv[i],"-port")) {
	testl	%eax, %eax	 # _5
	jne	.L7	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:31: 			PORT = atoi(argv[++i]);
	addl	$1, 732(%rsp)	 #, i
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:31: 			PORT = atoi(argv[++i]);
	movl	732(%rsp), %eax	 # i, tmp132
	cltq
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:31: 			PORT = atoi(argv[++i]);
	leaq	0(,%rax,8), %rdx	 #, _7
	movq	24(%rbp), %rax	 # argv, tmp133
	addq	%rdx, %rax	 # _7, _8
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:31: 			PORT = atoi(argv[++i]);
	movq	(%rax), %rax	 # *_8, _9
	movq	%rax, %rcx	 # _9,
	call	atoi	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:31: 			PORT = atoi(argv[++i]);
	movl	%eax, PORT(%rip)	 # _10, PORT
	jmp	.L8	 #
.L7:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:32: 		} else if(!strcmp(argv[i],"-ip")) {
	movl	732(%rsp), %eax	 # i, tmp134
	cltq
	leaq	0(,%rax,8), %rdx	 #, _12
	movq	24(%rbp), %rax	 # argv, tmp135
	addq	%rdx, %rax	 # _12, _13
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:32: 		} else if(!strcmp(argv[i],"-ip")) {
	movq	(%rax), %rax	 # *_13, _14
	leaq	.LC14(%rip), %rdx	 #, tmp136
	movq	%rax, %rcx	 # _14,
	call	strcmp	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:32: 		} else if(!strcmp(argv[i],"-ip")) {
	testl	%eax, %eax	 # _15
	jne	.L9	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:33: 			strncpy(GLOBAL_SERVER_IP, argv[++i], 15);
	addl	$1, 732(%rsp)	 #, i
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:33: 			strncpy(GLOBAL_SERVER_IP, argv[++i], 15);
	movl	732(%rsp), %eax	 # i, tmp137
	cltq
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:33: 			strncpy(GLOBAL_SERVER_IP, argv[++i], 15);
	leaq	0(,%rax,8), %rdx	 #, _17
	movq	24(%rbp), %rax	 # argv, tmp138
	addq	%rdx, %rax	 # _17, _18
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:33: 			strncpy(GLOBAL_SERVER_IP, argv[++i], 15);
	movq	(%rax), %rax	 # *_18, _19
	movl	$15, %r8d	 #,
	movq	%rax, %rdx	 # _19,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp139
	movq	%rax, %rcx	 # tmp139,
	call	strncpy	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:34: 			GLOBAL_SERVER_IP[15] = '\0';
	movb	$0, 15+GLOBAL_SERVER_IP(%rip)	 #, GLOBAL_SERVER_IP[15]
	jmp	.L8	 #
.L9:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:35: 		} else if(!strcmp(argv[i],"-winCNT")) {
	movl	732(%rsp), %eax	 # i, tmp140
	cltq
	leaq	0(,%rax,8), %rdx	 #, _21
	movq	24(%rbp), %rax	 # argv, tmp141
	addq	%rdx, %rax	 # _21, _22
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:35: 		} else if(!strcmp(argv[i],"-winCNT")) {
	movq	(%rax), %rax	 # *_22, _23
	leaq	.LC15(%rip), %rdx	 #, tmp142
	movq	%rax, %rcx	 # _23,
	call	strcmp	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:35: 		} else if(!strcmp(argv[i],"-winCNT")) {
	testl	%eax, %eax	 # _24
	jne	.L8	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:36: 			MAX_WIN_COUNT = atoi(argv[++i]);
	addl	$1, 732(%rsp)	 #, i
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:36: 			MAX_WIN_COUNT = atoi(argv[++i]);
	movl	732(%rsp), %eax	 # i, tmp143
	cltq
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:36: 			MAX_WIN_COUNT = atoi(argv[++i]);
	leaq	0(,%rax,8), %rdx	 #, _26
	movq	24(%rbp), %rax	 # argv, tmp144
	addq	%rdx, %rax	 # _26, _27
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:36: 			MAX_WIN_COUNT = atoi(argv[++i]);
	movq	(%rax), %rax	 # *_27, _28
	movq	%rax, %rcx	 # _28,
	call	atoi	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:36: 			MAX_WIN_COUNT = atoi(argv[++i]);
	movl	%eax, MAX_WIN_COUNT(%rip)	 # _29, MAX_WIN_COUNT
.L8:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:29: 	for(int i = 1; i < argc; i++) {
	addl	$1, 732(%rsp)	 #, i
.L6:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:29: 	for(int i = 1; i < argc; i++) {
	movl	732(%rsp), %eax	 # i, tmp145
	cmpl	16(%rbp), %eax	 # argc, tmp145
	jl	.L10	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	movl	PORT(%rip), %eax	 # PORT, PORT.0_30
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	testl	%eax, %eax	 # PORT.0_30
	je	.L11	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	movzbl	GLOBAL_SERVER_IP(%rip), %eax	 # GLOBAL_SERVER_IP[0], _31
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	testb	%al, %al	 # _31
	je	.L11	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	movl	MAX_WIN_COUNT(%rip), %eax	 # MAX_WIN_COUNT, MAX_WIN_COUNT.1_32
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	testl	%eax, %eax	 # MAX_WIN_COUNT.1_32
	jne	.L12	 #,
.L11:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:40: 	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	movl	$1, %ecx	 #,
	call	exit	 #
.L12:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:42: 	setupConsole();
	call	setupConsole	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:44: 	install_to_startup("BigBrotherClient");
	leaq	.LC16(%rip), %rax	 #, tmp146
	movq	%rax, %rcx	 # tmp146,
	call	install_to_startup	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:46: 	if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
	movl	$1, %edx	 #,
	movq	.refptr.ConsoleHandler(%rip), %rax	 #, tmp147
	movq	%rax, %rcx	 # tmp147,
	movq	__imp_SetConsoleCtrlHandler(%rip), %rax	 #, tmp148
	call	*%rax	 # tmp148
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:46: 	if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
	testl	%eax, %eax	 # _33
	jne	.L13	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:47: 		printf("\nCHYBA: Nepodarilo se nastavit odchytavani zavreni okna!\n");
	leaq	.LC17(%rip), %rax	 #, tmp149
	movq	%rax, %rcx	 # tmp149,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:48: 		exit(EXIT_FAILURE);
	movl	$1, %ecx	 #,
	call	exit	 #
.L13:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:52: 	sprintf(title,"Big Brother v%.1f - %d", VERSION, MAX_WIN_COUNT);
	movl	MAX_WIN_COUNT(%rip), %edx	 # MAX_WIN_COUNT, MAX_WIN_COUNT.2_34
	movabsq	$4607632778762754458, %rax	 #, tmp150
	movq	%rax, %rcx	 # tmp150, tmp151
	movq	%rcx, %xmm0	 # tmp151, tmp153
	movq	%rax, %rcx	 # tmp152, tmp154
	leaq	464(%rsp), %rax	 #, tmp155
	movl	%edx, %r9d	 # MAX_WIN_COUNT.2_34,
	movapd	%xmm0, %xmm2	 # tmp153,
	movq	%rcx, %r8	 # tmp154,
	leaq	.LC18(%rip), %rdx	 #, tmp156
	movq	%rax, %rcx	 # tmp155,
	call	sprintf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:55: 	gethostname(str,sizeof(str));
	leaq	448(%rsp), %rax	 #, tmp157
	movl	$16, %edx	 #,
	movq	%rax, %rcx	 # tmp157,
	movq	__imp_gethostname(%rip), %rax	 #, tmp158
	call	*%rax	 # tmp158
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:56: 	send_alert_packet(GLOBAL_SERVER_IP,PORT+1,ALERT,str);
	movl	PORT(%rip), %eax	 # PORT, PORT.3_35
	addl	$1, %eax	 #, _36
	leaq	448(%rsp), %rdx	 #, tmp159
	movq	%rdx, %r9	 # tmp159,
	movl	$2, %r8d	 #,
	movl	%eax, %edx	 # _36,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp160
	movq	%rax, %rcx	 # tmp160,
	call	send_alert_packet	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:58: 	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	movl	$-11, %ecx	 #,
	movq	__imp_GetStdHandle(%rip), %rax	 #, tmp161
	call	*%rax	 # tmp161
	movq	%rax, 720(%rsp)	 # tmp162, hConsole
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:59: 	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	movq	720(%rsp), %rax	 # hConsole, tmp163
	movl	$12, %edx	 #,
	movq	%rax, %rcx	 # tmp163,
	movq	__imp_SetConsoleTextAttribute(%rip), %rax	 #, tmp164
	call	*%rax	 # tmp164
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:60: 	printf("Spoustim monitoring klienta (Big Brother)...\n");
	leaq	.LC19(%rip), %rax	 #, tmp165
	movq	%rax, %rcx	 # tmp165,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:61: 	printf("Sledovany soubor: %s\n", "nullptr");
	leaq	.LC20(%rip), %rax	 #, tmp166
	movq	%rax, %rdx	 # tmp166,
	leaq	.LC21(%rip), %rax	 #, tmp167
	movq	%rax, %rcx	 # tmp167,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:62: 	printf("Server IP: %s:%d\n", GLOBAL_SERVER_IP, PORT);
	movl	PORT(%rip), %eax	 # PORT, PORT.4_37
	movl	%eax, %r8d	 # PORT.4_37,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp168
	movq	%rax, %rdx	 # tmp168,
	leaq	.LC22(%rip), %rax	 #, tmp169
	movq	%rax, %rcx	 # tmp169,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:63: 	printf("Verze BigBrothera: %.1f\n", VERSION);
	movabsq	$4607632778762754458, %rax	 #, tmp170
	movq	%rax, %rdx	 # tmp170, tmp171
	movq	%rdx, %xmm0	 # tmp171, tmp173
	movapd	%xmm0, %xmm1	 # tmp173,
	movq	%rax, %rdx	 # tmp174,
	leaq	.LC23(%rip), %rax	 #, tmp175
	movq	%rax, %rcx	 # tmp175,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:65: 	int timer = 0;
	movl	$0, 728(%rsp)	 #, timer
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:68: 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	leaq	32(%rsp), %rax	 #, tmp176
	movq	%rax, %rdx	 # tmp176,
	movl	$514, %ecx	 #,
	movq	__imp_WSAStartup(%rip), %rax	 #, tmp177
	call	*%rax	 # tmp177
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:68: 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
	testl	%eax, %eax	 # _38
	je	.L14	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:69: 		printf("Selhala inicializace Winsock.\n");
	leaq	.LC24(%rip), %rax	 #, tmp178
	movq	%rax, %rcx	 # tmp178,
	call	printf	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:70: 		return 1;
	movl	$1, %eax	 #, _87
	jmp	.L23	 #
.L14:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:73: 	SetConsoleTitle(title);
	leaq	464(%rsp), %rax	 #, tmp179
	movq	%rax, %rcx	 # tmp179,
	movq	__imp_SetConsoleTitleA(%rip), %rax	 #, tmp180
	call	*%rax	 # tmp180
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:75: 	system("pause");
	leaq	.LC25(%rip), %rax	 #, tmp181
	movq	%rax, %rcx	 # tmp181,
	call	system	 #
.L18:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:81: 				if(send_alert_packet(GLOBAL_SERVER_IP,PORT,HELLO,"HELLO") == 2) break;
	movl	PORT(%rip), %eax	 # PORT, PORT.5_39
	leaq	.LC26(%rip), %r9	 #,
	movl	$0, %r8d	 #,
	movl	%eax, %edx	 # PORT.5_39,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp182
	movq	%rax, %rcx	 # tmp182,
	call	send_alert_packet	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:81: 				if(send_alert_packet(GLOBAL_SERVER_IP,PORT,HELLO,"HELLO") == 2) break;
	cmpl	$2, %eax	 #, _40
	je	.L25	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:82: 				Sleep(2000);
	movl	$2000, %ecx	 #,
	movq	__imp_Sleep(%rip), %rax	 #, tmp183
	call	*%rax	 # tmp183
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:81: 				if(send_alert_packet(GLOBAL_SERVER_IP,PORT,HELLO,"HELLO") == 2) break;
	jmp	.L18	 #
.L25:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:81: 				if(send_alert_packet(GLOBAL_SERVER_IP,PORT,HELLO,"HELLO") == 2) break;
	nop	
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:84: 			Sleep(500);
	movl	$500, %ecx	 #,
	movq	__imp_Sleep(%rip), %rax	 #, tmp184
	call	*%rax	 # tmp184
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:85: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,CONFIG,"CONFIG") != 2) continue;
	movl	PORT(%rip), %eax	 # PORT, PORT.6_41
	leaq	.LC27(%rip), %r9	 #,
	movl	$1, %r8d	 #,
	movl	%eax, %edx	 # PORT.6_41,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp185
	movq	%rax, %rcx	 # tmp185,
	call	send_alert_packet	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:85: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,CONFIG,"CONFIG") != 2) continue;
	cmpl	$2, %eax	 #, _42
	jne	.L26	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:86: 			Sleep(500);
	movl	$500, %ecx	 #,
	movq	__imp_Sleep(%rip), %rax	 #, tmp186
	call	*%rax	 # tmp186
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:87: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,START,"START") != 2) continue;
	movl	PORT(%rip), %eax	 # PORT, PORT.7_43
	leaq	.LC28(%rip), %r9	 #,
	movl	$5, %r8d	 #,
	movl	%eax, %edx	 # PORT.7_43,
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp187
	movq	%rax, %rcx	 # tmp187,
	call	send_alert_packet	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:87: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,START,"START") != 2) continue;
	cmpl	$2, %eax	 #, _44
	jne	.L27	 #,
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:88: 			break;
	jmp	.L22	 #
.L26:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:85: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,CONFIG,"CONFIG") != 2) continue;
	nop	
	jmp	.L18	 #
.L27:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:87: 			if(send_alert_packet(GLOBAL_SERVER_IP,PORT,START,"START") != 2) continue;
	nop	
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:79: 		while(1) {
	jmp	.L18	 #
.L22:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:92: 			monitor_environment(GLOBAL_SERVER_IP);
	leaq	GLOBAL_SERVER_IP(%rip), %rax	 #, tmp188
	movq	%rax, %rcx	 # tmp188,
	call	monitor_environment	 #
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:94: 			if (timer % 10 == 0) {
	movl	728(%rsp), %ecx	 # timer, tmp189
	movslq	%ecx, %rax	 # tmp189, tmp190
	imulq	$1717986919, %rax, %rax	 #, tmp190, tmp191
	shrq	$32, %rax	 #, tmp192
	sarl	$2, %eax	 #, tmp193
	movl	%ecx, %r8d	 # tmp189, tmp194
	sarl	$31, %r8d	 #, tmp194
	subl	%r8d, %eax	 # tmp194, tmp193
	movl	%eax, %edx	 # tmp193, _45
	movl	%edx, %eax	 # _45, tmp195
	sall	$2, %eax	 #, tmp195
	addl	%edx, %eax	 # _45, tmp195
	addl	%eax, %eax	 # tmp196
	subl	%eax, %ecx	 # tmp195, tmp189
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:98: 			timer++;
	addl	$1, 728(%rsp)	 #, timer
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:99: 			Sleep(1000); 
	movl	$1000, %ecx	 #,
	movq	__imp_Sleep(%rip), %rax	 #, tmp197
	call	*%rax	 # tmp197
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:92: 			monitor_environment(GLOBAL_SERVER_IP);
	jmp	.L22	 #
.L23:
 # C:\Users\lukas\Desktop\Big Brother\BigBrotherClient\main.c:105: }
	leave	
	ret	
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 11.5.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	__mingw_vsprintf;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	atoi;	.scl	2;	.type	32;	.endef
	.def	strncpy;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	setupConsole;	.scl	2;	.type	32;	.endef
	.def	install_to_startup;	.scl	2;	.type	32;	.endef
	.def	send_alert_packet;	.scl	2;	.type	32;	.endef
	.def	system;	.scl	2;	.type	32;	.endef
	.def	monitor_environment;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.ConsoleHandler, "dr"
	.globl	.refptr.ConsoleHandler
	.linkonce	discard
.refptr.ConsoleHandler:
	.quad	ConsoleHandler
