1  #include <stdio.h>
2  #include <stdlib.h>
3  #include <string.h>
4  #include <unistd.h>
5  #include <fcntl.h> 
6  #include <termios.h>
7  #include <errno.h> 
8  #include <sys/ioctl.h>
9  #include <time.h>
10 #include <string.h>
11 #define blocksize 255
12 #define DEBUG 1
13 
14 int sfd;                                          //File descriptor
15 char buf[blocksize];
16 
17 void delay(void)
18 {
19 	int c,d;
20 	for(c=1;c<=32767;c++)
21 	  for(d=1;d<=32767;d++)
22 	  {}
23 }
24 void delay_less(void)
25 {
26 	
27         int c,d;
28         for(c=1;c<=20000;c++)
29           for(d=1;d<=20000;d++)
30           {}
31 }
32 
33 int initWiFi()
34 {	
35 	//Relinquish access of serial port on Raspberry Pi for our use
36 	system("sudo systemctl stop serial-getty@ttyAMA0.service");
37 	
38 	//Open the file /dev/ttyAMA0 in read/write mode
39  	sfd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
40 	
41 	//Check whether the file has opened or not
42  	if (sfd == -1) 
43 	{
44   		printf("Error no is : %d\n", errno);
45   		printf("Error description is : %s\n", strerror(errno));
46   		return -1;
47  	}
48 	
49 	//Setting the UART baud rate,stop bits, flags etc
50  	struct termios options;
51 	//Fills the struct with current values specified by the file descriptor
52  	tcgetattr(sfd, &options);	 
53 	cfsetspeed(&options, B9600);
54  	cfmakeraw(&options);		  //Enable raw mode on input/output
55  	options.c_cflag &= ~CSTOPB;   //cflag = control options
56  	options.c_cflag |= CLOCAL     //Ignore modem control lines
57  	options.c_cflag |= CREAD;     //Enables read operation
58  	options.c_cc[VTIME] = 1;      //timeout value
59  	options.c_cc[VMIN] = blocksize;  //Min no. of characters before the call is considered satisfied
60 	//Stores values back in the device, TCSANOW-Immediate change
61  	tcsetattr(sfd, TCSANOW, &options);
62 };
63 
64 //Receive data from the opened file
65 int getBlock()
66 {
67  int bytes;
68  struct timespec pause;
69  pause.tv_sec = 0;
70  pause.tv_nsec = 100000000;
71  nanosleep(&pause, NULL);
72  memset(buf, '\0', sizeof (buf));
73  //Return the number of characters waiting
74  ioctl(sfd, FIONREAD, &bytes);
75  if (bytes == 0)return 0;
76  int count = read(sfd, buf, blocksize - 1);
77  buf[count] = 0;
78  if (DEBUG) {
79   printf("%s", buf);
80   fflush(stdout);
81  }
82  return count;
83 }
84 
85 int main(int argc, char** argv)
86 {
87 
88 	initWiFi();
89 	delay_less();
90 	
91 	//write lua command to file which in turn sends to esp via UART for execution
92 	//Sending data to Thingspeak channel
93 	char file_name1[]= "thingspeaksend.lua";
94 	dprintf(sfd,"dofile(\"%s\")\r\n",file_name1);
95 	delay();
96 	delay();
97 	delay();
98 	delay();
99 	delay();
100	delay();
101	delay();
102	delay();
103	delay();
104	delay();
105	delay();
106	delay();
107	delay();
108	delay();
109	delay();
110	
111	//Receiving last send data from Thingspeak Channel
112	char file_name[]= "script1.lua";
113	dprintf(sfd,"dofile(\"%s\")\r\n",file_name);
114	return (EXIT_SUCCESS);
115}