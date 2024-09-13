// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <cstring>
// #include <fstream>
// using namespace std;

// #define MAXLEN 1024
// int mode, padding;
// //mode 1:AES_128_ECB,2:AES_192_ECB,3:AES_256_ECB,4:AES_128_CBC,5:AES_192_CBC,6:AES_256_CBC

// int wordLength;
// int keyword;//密钥有多少个字长
// int encryptTimes;//轮数
// int beforeTimes;
// int keybyte;
// int forming;//1：字符串 2:十六进制 3:二进制 

// unsigned char xtime (unsigned char input);
// void bytesub(unsigned char S_BOX[][16], unsigned char B[][4]);
// void shiftrow(unsigned char B[][4]);
// void mixcolumn(unsigned char input[][4]);
// void invbytesub(unsigned char N_S_BOX[][16], unsigned char B[][4]);
// void invshiftrow(unsigned char B[][4]);
// void invmixcolum(unsigned char input[][4]);
// int encrypt_ecb(unsigned char S_BOX[][16]);
// int decrypt_ecb(unsigned char S_BOX[][16], unsigned char N_S_BOX[][16]);
// int encrypt_cbc(unsigned char S_BOX[][16]);
// int decrypt_cbc(unsigned char S_BOX[][16], unsigned char N_S_BOX[][16]);

// static int getIntFromChar(char c);
// static void convertArrayToStr(int array[4][4], char* str);
// static void convertArrayToStr16(unsigned char chArray[4][4], unsigned char B[4][4], int l);
// void writeStrToFile(char* str, int len, char* fileName);
// void xorWithiv(unsigned char iv[4][4], unsigned char B[4][4]);
// void setKeyLength(int length);
// int readStrFromFile(char* fileName, char* str);
// void setKey(unsigned char S_BOX[][16],unsigned char keys[][60]);//设置密钥

// //把一个字符转变成整型
// static int getIntFromChar(char c) {
// 	int result = (int)c;
// 	return result & 0x000000ff;
// }

// //把4X4数组转回字符串
// static void convertArrayToStr(int array[4][4], char* str) {
// 	int i, j;
// 	for (i = 0; i < 4; i++)
// 		for (j = 0; j < 4; j++)
// 			*str++ = (char)array[j][i];
// }

// //把4X4数组放进十六进制存放的字符串 
// static void convertArrayToStr16(unsigned char chArray[], unsigned char B[4][4], int l){
// 	int i, j;
// 	for(i = 0; i < 4; i ++){
// 		for(j = 0; j < 4; j ++){
// 			chArray[l] = B[j][i];
// 			l++;
// 		}
// 	}
// } 

// //把字符串写进文件
// void writeStrToFile(char* str, int len, char* fileName) {
// 	FILE* fp;
// 	fp = fopen(fileName, "wb");
// 	for (int i = 0; i < len; i++)
// 		putc(str[i], fp);
// 	fclose(fp);
// }

// //从文件中读取字符串
// int readStrFromFile(char* fileName, char* str) {
// 	FILE* fp = fopen(fileName, "rb");
// 	if (fp == NULL) {
// 		printf("打开文件出错，请确认文件存在当前目录下！\n");
// 		exit(0);
// 	}

// 	int i;
// //	for (i = 0; i < MAXLEN && (str[i] = getc(fp)) != EOF; i++);
// 	for (i = 0; i < MAXLEN && !feof(fp); i++){
// 		str[i] = getc(fp);
// 	}
// 	i--;

// 	if (i >= MAXLEN) {
// 		printf("解密文件过大！\n");
// 		exit(0);
// 	}

// 	str[i] = '\0';
// 	fclose(fp);
// 	return i;
// }

// //和偏移向量进行异或
// void xorWithiv(unsigned char iv[4][4], unsigned char B[4][4]){
//     for(int i = 0; i <= 3; i ++){
//         for(int j = 0; j <= 3; j ++){
//             B[i][j]^= iv[i][j];
//         }
//     }
// } 

// void setKeyLength(int length){

//     keybyte = length>>3;//密钥的字节数量
//     keyword = keybyte>>2;//已经有了多少字

//     encryptTimes = keyword + 6;
//     beforeTimes = encryptTimes-1;
//     wordLength = (encryptTimes+1)<<2;//总字数，

// }

// //用于扩展密钥的轮常量
// const static unsigned char rcon[13][4] =
// {
// 	{0x01,0x0,0x0,0x0},{0x2,0x0,0x0,0x0},{0x4,0x0,0x0,0x0},{0x8,0x0,0x0,0x0},{0x10,0x0,0x0,0x0},
// 	{0x20,0x0,0x0,0x0},{0x40,0x0,0x0,0x0},{0x80,0x0,0x0,0x0},{0x1b,0x0,0x0,0x0},{0x36,0x0,0x0,0x0},
// 	{0x6c,0x0,0x0,0x0},{0xd8,0x0,0x0,0x0},{0xab,0x0,0x0,0x0}
// };

// //输入密钥，并进行扩展

// void setKey(unsigned char S_BOX[][16],unsigned char keys[][60]){
	
// 	char str[36];
// 	int k, i, j, len;
// 	unsigned char temp[4];

// 	if(mode ==1 ||mode == 4){
// 		printf("请输入16位长度密钥:\n");
// 		setKeyLength(128);
// 	}
	
// 	if(mode ==2 ||mode == 5){
// 		printf("请输入24位长度密钥:\n");
// 		setKeyLength(192);
// 	}
	
// 	if(mode ==3 ||mode == 6){
// 		printf("请输入32位长度密钥:\n");
// 		setKeyLength(256);
// 	}
    
//     scanf("%s", str);
//     printf("\n");
    
//     len = strlen(str);
//     for(i = len; i < keybyte; i++){
//     	str[i] = 0;
// 	}
// 	str[len] = '\0';

// 	k = 0;
// 	for(i = 0; i < keyword; i ++)
//         for(j = 0; j <= 3; j ++){
//         	keys[j][i] = getIntFromChar(str[k]);
//         	k ++;
// 		}

//     for(i = keyword; i < wordLength;  i++){ //后40个word
//         if(i%keyword!=0){//不是4的倍数，word[i] = word[i-4]^word[i-1]
//         	for(j = 0; j < 4; j++){
//         		temp[j] = keys[j][i - 1];
// 			}
			
//             for(j = 0; j < 4; j ++){
//                 if(i % keyword == 4 && keyword > 6){
//                 	temp[j] = S_BOX[temp[j] / 16][temp[j] % 16];
//                 }
//                 keys[j][i] = keys[j][i - keyword] ^ temp[j];
//             }
//         }
        
//         else{//4的倍数，word[i] = word[i-4]^T(word[i-1]),T代表字节左移一位，S盒字节代换，根据轮数与轮常量进行异或
//         	for(j = 0; j < 4; j++){
//         		temp[j] = keys[j][i - 1];
// 			}
//             for(j = 0; j < 4; j ++){           
//                 temp[j] = keys[(j + 1) % 4][i - 1];
//                 temp[j] = S_BOX[temp[j] / 16][temp[j] % 16];
//                 temp[j] = temp[j] ^ rcon[(i / keyword - 1)][j];
//                 keys[j][i] = keys[j][i - keyword] ^ temp[j];
//             }

//         }
//     }
// }

// //列混淆运算用到的乘2函数
// unsigned char xtime (unsigned char input){    // x乘法('02'乘法)

//     int temp;
//     temp = input << 1;
    
//     if(input & 0x80){
//         temp ^= 0x1b;
//     }

//     return temp;

// }

// //列混淆运算
// void mixcolumn(unsigned char input[][4]){  //列混淆

//     int i, j;
//     unsigned char output[4][4];

//     for(j = 0; j <= 3; j++)
//         for(i = 0; i <= 3; i++)
//             output[i][j] = xtime(input[i%4][j]) //0x02乘法
//                            ^ ( input[ ( i + 1 ) % 4][j] ^ xtime( input[ ( i + 1 ) % 4][j] ) ) //0x03乘法
//                            ^ input[ ( i + 2 ) % 4][j]  //0x01乘法
//                            ^ input[ ( i + 3 ) % 4][j]; //0x01乘法

//     for(i = 0; i <= 3; i ++)
//         for(j = 0; j <= 3; j ++)
//             input[i][j] = output[i][j];

// }

// //行移位

// void shiftrow(unsigned char B[][4]){

//     int i, temp;
//     temp = B[1][0];

//     for(i = 0; i <= 2; i ++)
//         B[1][i] = B[1][i + 1];
//     B[1][3] = temp;

//     for(i = 0; i <= 1; i ++){

//         temp = B[2][i];
//         B[2][i] = B[2][i + 2];
//         B[2][i + 2] = temp;

//     }

//     temp = B[3][3];
//     for(i = 3; i >= 1; i --)
//         B[3][i] = B[3][i - 1];
//     B[3][0] = temp;

// }

// //字节变换
// void bytesub(unsigned char S_BOX[][16], unsigned char B[][4]){

//     register int i, j;
    
//     for(i = 0; i <= 3; i ++)
//         for(j = 0; j <= 3; j ++)
//             B[i][j] = S_BOX[B[i][j] / 16][B[i][j] % 16];

// }

// //逆行移位
// void invshiftrow(unsigned char B[][4]){

//     int i, temp;

//     temp = B[1][3];

//     for(i = 3; i >= 1; i --)
//         B[1][i] = B[1][i - 1];
//     B[1][0] = temp;

//     for(i = 0; i <= 1; i ++){
//         temp = B[2][i];
//         B[2][i] = B[2][i + 2];
//         B[2][i + 2] = temp;
//     }

//     temp = B[3][0];

//     for(i = 0; i <= 2; i ++)
//         B[3][i] = B[3][i + 1];
//     B[3][3] = temp;

// }

// //逆列混淆运算

// void invmixcolum(unsigned char input[][4]){

//     int i, j;
//     unsigned char output[4][4];

//     for(j = 0; j < 4; j++)
//         for(i = 0; i < 4; i++)
//             output[i][j] = (xtime(xtime(xtime(input[i % 4][j]))) ^ xtime(xtime(input[i % 4][j])) ^ xtime(input[i % 4][j])) //0x0E乘法
//                            ^ (xtime(xtime(xtime(input[ ( i + 1 ) % 4][j]))) ^ xtime(input[ ( i + 1 ) % 4][j]) ^ input[ ( i + 1 ) % 4][j]) //0x0B乘法
//                            ^ (xtime(xtime(xtime(input[ ( i + 2 ) % 4][j]))) ^ xtime(xtime(input[ ( i + 2 ) % 4][j])) ^ input[ ( i + 2 ) % 4][j]) //0x0D乘法
//                            ^ (xtime(xtime(xtime(input[ ( i + 3 ) % 4][j]))) ^ input[ ( i + 3 ) % 4][j]); //0x09乘法

//     for(i = 0; i <= 3; i ++)
//         for(j = 0; j <= 3; j ++)
//             input[i][j] = output[i][j];

// }

// //逆字节变换
// void invbytesub(unsigned char N_S_BOX[][16], unsigned char B[][4]){

//     register int i, j;

//     for(i = 0; i <= 3; i ++)
//         for(j = 0; j <= 3; j ++)
//             B[i][j] = N_S_BOX[B[i][j] / 16][B[i][j] % 16];

// }

// int encrypt_ecb(unsigned char S_BOX[][16]){
 
//     unsigned char e, B[4][4];
//     unsigned char keys[4][60];
//     int i, j;
//     int level;
    
//     char str[MAXLEN],result[MAXLEN]; 
//     int cArray[4][4];
//     int len, clen, k, l, padLength, textwhere;
//     unsigned char strr[MAXLEN];
    
//     if(forming == 1){
//     	printf("直接输入字符串请输入：1\n");
//     	printf("从本地文件读取字符串请输入：2\n\n");
//     	printf("请输入选择：");
//     	scanf("%d",&textwhere);
    	
//     	if(textwhere == 1){
//     		printf("\n请输入明文：\n");
//     		scanf("%s", str);
//     		getchar();
//     		len = strlen(str);
// 		}
		
// 		else if(textwhere == 2){
// 			char fileName[64];
//     		printf("\n请输入要加密的文件名，该文件必须和本程序在同一个目录\n");
//     		if (scanf("%s", fileName) == 1){
//     			clen = readStrFromFile(fileName, str);
// 			}
// 			len = clen;
// 		}
// 		padLength = 16 - len % 16; //需要填充多少个字符 
//     	for(i = len; i < padLength + len; i ++){
//     		str[i] = (char)padLength;
// 		}
// 		len += padLength;
// 		str[len] = '\0';
// 	}
	
// 	else if(forming == 2){
    	
//     	printf("请输入十六进制明文：\n");
//     	i = 0;
//     	while(1){
// 			scanf("%x",&strr[i]);
// 			i++;
// 			if(cin.get()=='\n')
// 				break;
// 		}
// 		//	getchar();
//     	len = i;
//     	padLength = 16 - len % 16;
//     	for(i = len; i < padLength + len; i ++){
//     		strr[i] = (unsigned char)padLength;
// 		}
// 		len += padLength;
		 		
// 	}
	
// 	else if(forming == 3){
		
// 		char fileName[64];
// 		printf("请输入要加密的二进制文件名，比如'test.dat'，该文件必须和本程序在同一个目录\n");
// 		scanf("%s", fileName);
// 		ifstream file(fileName, ios::out | ios::binary);
//    		if (!file)
//     	{
//         	cout << "Error opening file.";
//         	exit(0);
//     	}
//     	i = 0;
//     	while(file.read((char *)&strr[i], sizeof(unsigned char))){
//     		i++;
// 		}
// 		file.close();
			
// 		len = i;
// //		printf("len=%d",len);
// 		padLength = 16 - len % 16;
//     	for(i = len; i < padLength + len; i ++){
//     		strr[i] = (unsigned char)padLength;
// 		}
// 		len += padLength;
		
// 	}

//     putchar('\n');
//     setKey(S_BOX, keys);
// //    keyexpansion(S_BOX, keys);
    
//     k = 0;
    
//     for(l = 0; l < len; l += 16){
    	
//     	k = l;
//     	for(i = 0; i <= 3; i ++){
//     		for(j = 0; j <= 3; j ++){
//     			if(forming == 1)
//     				B[j][i] = getIntFromChar(str[k]);
//     			else if(forming == 2 || forming == 3)
//     				B[j][i] = strr[k];
				
//     			k++;
// 			}
// 		}				
	
// 		//轮密钥加 
// 		for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++){
//             	B[i][j] ^= keys[i][j];
//         	}
        	
        	
//         for(level = 1; level <= beforeTimes; level ++){    //前n-1轮循环 
//         	bytesub(S_BOX, B); //字节代换 
//         	shiftrow(B);  //行移位 
//         	mixcolumn(B);  //列混合 

// 			//轮密钥加 
//         	for(i = 0; i <= 3; i ++)
//         	    for(j = 0; j <= 3; j ++)
//         	        B[i][j] ^= keys[i][level * 4 + j];        	                	        
//     	}

//     	bytesub(S_BOX, B);               //第n轮循环
//     	shiftrow(B);
    	
//     	for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++){ 
//             	B[i][j] ^= keys[i][wordLength - 4 + j];
//             	cArray[i][j] = (int)B[i][j];      
// //            	printf("%x ",B[i][j]);
//         	}
		
// 		for(i=0;i<4;i++){
// 			for(j=0;j<4;j++){
// 				printf("%x ",B[j][i]);
// 			}
// 		} 
// 		printf("\n");
        	
//         convertArrayToStr(cArray, result+l);
	
// 	}
// 	result[len]='\0';

// 	char fileName[64];
// 	printf("请输入你想要写进的文件名，比如'test.txt':\n");
// 	if (scanf("%s", fileName) == 1) {
// 		writeStrToFile(result, len, fileName);
// 		printf("已经将密文写进%s中了,可以在运行该程序的当前目录中找到它。\n", fileName);
// 	}

//     return 0;
// }

// int encrypt_cbc(unsigned char S_BOX[][16]){
 
//     unsigned char e, B[4][4], iv[4][4];
//     unsigned char keys[4][60];
//     int i, j;
//     int level, padLength;
    
//     char str[MAXLEN],result[MAXLEN]; 
//     int cArray[4][4];
//     int len, clen, k, l, textwhere;
//     unsigned char strr[MAXLEN];

// 	if(forming == 1){
//     	printf("直接输入字符串请输入：1\n");
//     	printf("从本地文件读取字符串请输入：2\n\n");
//     	printf("请输入选择：");
//     	scanf("%d",&textwhere);
    	
//     	if(textwhere == 1){
//     		printf("\n请输入明文：\n");
//     		scanf("%s", str);
//     		getchar();
//     		len = strlen(str);
// 		}
		
// 		else if(textwhere == 2){
// 			char fileName[64];
//     		printf("请输入要加密的文件名，该文件必须和本程序在同一个目录\n");
//     		if (scanf("%s", fileName) == 1){
//     			clen = readStrFromFile(fileName, str);
// 			}
// 			len = clen;
// 		}
// 		padLength = 16 - len % 16; //需要填充多少个字符 
//     	for(i = len; i < padLength + len; i ++){
//     		str[i] = (char)padLength;
// 		}
// 		len += padLength;
// 		str[len] = '\0';
// 	}
	
// 	else if(forming == 2){
    	
//     	printf("请输入十六进制明文：\n");
//     	i = 0;
//     	while(1){
// 			scanf("%x",&strr[i]);
// 			i++;
// 			if(cin.get()=='\n')
// 				break;
// 		}
// 		//	getchar();
//     	len = i;
//     	padLength = 16 - len % 16;
//     	for(i = len; i < padLength + len; i ++){
//     		strr[i] = (unsigned char)padLength;
// 		}
// 		len += padLength;
		 		
// 	}
	
// 	else if(forming == 3){
		
// 		char fileName[64];
// 		printf("请输入要加密的二进制文件名，比如'test.dat'，该文件必须和本程序在同一个目录\n");
// 		scanf("%s", fileName);
// 		ifstream file(fileName, ios::out | ios::binary);
//    		if (!file)
//     	{
//         	cout << "Error opening file.";
//         	exit(0);
//     	}
//     	i = 0;
//     	while(file.read((char *)&strr[i], sizeof(unsigned char))){
//     		i++;
// 		}
// 		file.close();
			
// 		len = i;
// //		printf("len=%d",len);
// 		padLength = 16 - len % 16;
//     	for(i = len; i < padLength + len; i ++){
//     		strr[i] = (unsigned char)padLength;
// 		}
// 		len += padLength;
		
// 	}

//     putchar('\n');   
    
//     //keyexpansion(S_BOX, keys);
//     setKey(S_BOX, keys);
    
//     k = 0;
    
//     for(l = 0; l < len; l += 16){
    	
//     	k = l;
//     	for(i = 0; i <= 3; i ++){
//     		for(j = 0; j <= 3; j ++){
//     			if(forming == 1)
//     				B[j][i] = getIntFromChar(str[k]);
//     			else if(forming == 2 || forming == 3)
//     				B[j][i] = strr[k];
//     			k++;
// 			}
// 		}
// 		if(l == 0){
// 			for(i = 0; i < 4; i ++){
// 				for(j = 0; j < 4; j ++){
// 					iv[i][j] = 0;					
// 				}
// 			}

// 		}
		
// 		xorWithiv(iv, B); //和偏移向量进行异或 
	
// 		//轮密钥加 
// 		for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++){
//             	B[i][j] ^= keys[i][j];
//         	}
        	  	
//         for(level = 1; level <= beforeTimes; level ++){    //1到9轮循环
//         	bytesub(S_BOX, B); //字节代换 
//         	shiftrow(B);  //行移位 
//         	mixcolumn(B);  //列混合 

// 			//这里似乎又是轮密钥加 
//         	for(i = 0; i <= 3; i ++)
//         	    for(j = 0; j <= 3; j ++)
//         	        B[i][j] ^= keys[i][level * 4 + j];        	                	        
//     	}

//     	bytesub(S_BOX, B);               //第10轮循环
//     	shiftrow(B);
    	
//     	for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++){ 
//             	B[i][j] ^= keys[i][wordLength - 4 + j];
//             	cArray[i][j] = (int)B[i][j];      
//         	} 
        	
//         convertArrayToStr(cArray, result+l);
	
// 		for(i = 0; i < 4; i ++){
// 			for(j = 0; j < 4; j ++){
// 				iv[i][j] = B[i][j];
// 			}
// 		}
// 		for(i=0;i<4;i++){
// 			for(j=0;j<4;j++){
// 				printf("%x ",B[j][i]);
// 			}
// 		} 
// 		printf("\n");
  	
// 	}
// 	result[len]='\0';

// 	char fileName[64];
// 	printf("请输入你想要写进的文件名，比如'test.txt':\n");
// 	if (scanf("%s", fileName) == 1) {
// 		writeStrToFile(result, len, fileName);
// 		printf("已经将密文写进%s中了,可以在运行该程序的当前目录中找到它。\n", fileName);
// 	}

//     return 0;
// }

// int decrypt_ecb(unsigned char S_BOX[][16], unsigned char N_S_BOX[][16]){ 
 
//     unsigned char B[4][4];
//     unsigned char keys[4][60];
//     int temp, clen, i, j;
//     int level, padLength;
    
//     char str[MAXLEN];
//     char result[MAXLEN];
//     int cArray[4][4];
//     unsigned char chArray[MAXLEN];
//     int len, l, k;  
    
//     char fileName[64];
//     printf("请输入要解密的文件名，该文件必须和本程序在同一个目录\n");
//     if (scanf("%s", fileName) == 1){
//     	clen = readStrFromFile(fileName, str);
// 	}

//     len = clen;
// 	putchar('\n');
    
//     //keyexpansion(S_BOX, keys);
//     setKey(S_BOX, keys);
    
//     printf("解密结果为:\n");

// 	for(l = 0; l < len; l +=16){
//     	k = l;
//     	for(i = 0;i <=3; i ++){
//     		for(j = 0; j <=3; j ++){
//     			B[j][i] = getIntFromChar(str[k]);
//     			k ++;
// 			}
// 		}

// 		for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++)
//             	B[i][j] ^= keys[i][j + wordLength - 4];
		
// 		for(level = 1; level <= beforeTimes; level ++){

//         	invshiftrow(B);
//         	invbytesub(N_S_BOX, B);

//         	for(i = 0; i <= 3; i ++)
//         	    for(j = 0; j <= 3; j ++)
//         	        B[i][j] ^= keys[i][wordLength - 4 - level * 4 + j];

//         	invmixcolum(B);
//     	}

//     	invshiftrow(B);
//     	invbytesub(N_S_BOX, B);
    	
//     	if(forming == 1){
//     		for(i = 0; i <= 3; i ++)
//         		for(j = 0; j <= 3; j ++){
//         		      B[i][j] ^= keys[i][j];
//         		    cArray[i][j] = (int)B[i][j];		           	
// 				}
	
// 			convertArrayToStr(cArray, result+l);
// 		}
		
// 		else if(forming == 2 || forming ==3){
// 			for(i = 0; i <= 3; i ++)
//         		for(j = 0; j <= 3; j ++){
//         		      B[i][j] ^= keys[i][j];	           	
// 				}
	
// 			convertArrayToStr16(chArray, B, l);
// 		}			
// 	}
	
// 	if(forming == 1){
// 		padLength = (int)result[len-1];
// 		result[len-padLength]='\0';
			
// 		printf("%s",result);
// 		putchar('\n');
// 	}
	
// 	else if(forming == 2){
// 		padLength = (int)chArray[len-1];
// 		len -= padLength;
		
// 		for(i = 0; i < len; i ++){
// 			printf("%x ",chArray[i]);
// 		}
// 		putchar('\n');
// 	}
	
// 	else if(forming == 3){
// 		padLength = (int)chArray[len-1];
// 		len -= padLength;

// 		printf("请输入你想要存放的二进制文件名，比如'test.dat':\n");
// 		scanf("%s", fileName);
			
// 		ofstream file(fileName, ios::out | ios::binary);
// 		for(i = 0; i < len; i ++){
// 			file.write((char*)&chArray[i], sizeof(unsigned char));
// 		}
// 		printf("已经将密文写进%s中了,可以在运行该程序的当前目录中找到它。\n", fileName);
// 	}

//     return 0;
// }

// int decrypt_cbc(unsigned char S_BOX[][16], unsigned char N_S_BOX[][16]){
 
//     unsigned char B[4][4], iv[4][4], bef[4][4];
//     unsigned char keys[4][60];
//     int temp, clen, i, j;
//     int level;
    
//     char str[MAXLEN];
//     char result[MAXLEN];
//     int cArray[4][4];
//     unsigned char chArray[MAXLEN];
//     int len, l, k, padLength;
    
//     char fileName[64];
//     printf("请输入要解密的文件名，该文件必须和本程序在同一个目录\n");
//     if (scanf("%s", fileName) == 1){
//     	clen = readStrFromFile(fileName, str);
// 	}

//     len = clen;
// 	putchar('\n');
    
//     //keyexpansion(S_BOX, keys);
//     setKey(S_BOX, keys);
    
//     printf("解密结果为:\n");

// 	for(l = 0; l < len; l +=16){
//     	k = l;
//     	for(i = 0;i <=3; i ++){
//     		for(j = 0; j <=3; j ++){
//     			B[j][i] = getIntFromChar(str[k]);
//     			bef[j][i] = B[j][i];
//     			k ++;
// 			}
// 		}

// 		if(l == 0){
// 			for(i = 0; i < 4; i ++){
// 				for(j = 0; j < 4; j ++){
// 					iv[i][j] = 0;
// 				}
// 			}
// 		}

// 		for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++)
//             	B[i][j] ^= keys[i][j + wordLength - 4];
		
// 		for(level = 1; level <= beforeTimes; level ++){

//         	invshiftrow(B);
//         	invbytesub(N_S_BOX, B);

//         	for(i = 0; i <= 3; i ++)
//         	    for(j = 0; j <= 3; j ++)
//         	        B[i][j] ^= keys[i][wordLength - 4 - level * 4 + j];

//         	invmixcolum(B);
//     	}

//     	invshiftrow(B);
//     	invbytesub(N_S_BOX, B);
    	
//     	for(i = 0; i <= 3; i ++)
//         	for(j = 0; j <= 3; j ++){
//         	      B[i][j] ^= keys[i][j];			           	
// 			}
		
// 		xorWithiv(iv, B);

// 		if(forming == 1){
// 			for(i = 0; i <= 3; i ++){
// 				for(j = 0; j <= 3; j ++){
// 					iv[i][j] = bef[i][j];
// 					cArray[i][j] = (int)B[i][j]; 
// 				}
// 			}
			
// 			convertArrayToStr(cArray, result+l);
// 		}
		
// 		else if(forming == 2 || forming == 3){
// 			for(i = 0; i <= 3; i ++){
// 				for(j = 0; j <= 3; j ++){
// 					iv[i][j] = bef[i][j];
// 				}
// 			}
			
// 			convertArrayToStr16(chArray, B, l);
// 		}					
// 	}
	
// 	if(forming == 1){
// 		padLength = (int)result[len-1];
// 		result[len-padLength]='\0';
			
// 		printf("%s",result);
// 		putchar('\n');
// 	}
	
// 	else if(forming == 2){
// 		padLength = (int)chArray[len-1];
// 		len -= padLength;
		
// 		for(i = 0; i < len; i ++){
// 			printf("%x ",chArray[i]);
// 		}
// 		putchar('\n');
// 	}
	
// 	else if(forming == 3){
// 		padLength = (int)chArray[len-1];
// 		len -= padLength;

// 		printf("请输入你想要存放的二进制文件名，比如'test.dat':\n");
// 		scanf("%s", fileName);
			
// 		ofstream file(fileName, ios::out | ios::binary);
// 		for(i = 0; i < len; i ++){
// 			file.write((char*)&chArray[i], sizeof(unsigned char));
// 		}
// 		printf("已经将密文写进%s中了,可以在运行该程序的当前目录中找到它。\n", fileName);
// 	}

//     return 0;

// }

// int main()
// {

//     unsigned char S_BOX[16][16] =
//     {
//         0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
//         0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
//         0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
//         0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
//         0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
//         0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
//         0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
//         0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
//         0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
//         0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
//         0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
//         0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
//         0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
//         0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
//         0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
//         0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
//         0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
//         0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
//         0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
//         0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
//         0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
//         0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
//         0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
//         0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
//         0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
//         0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
//         0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
//         0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
//         0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
//         0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
//         0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 
//         0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
//     };

//     unsigned char N_S_BOX[16][16] =
//     {
//         0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
//         0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
//         0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
//         0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
//         0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
//         0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
//         0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
//         0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
//         0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
//         0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
//         0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
//         0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
//         0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
//         0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
//         0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
//         0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
//         0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
//         0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
//         0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
//         0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
//         0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
//         0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
//         0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
//         0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
//         0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
//         0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
//         0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
//         0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
//         0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
//         0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
//         0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
//         0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
//     };

//     int choose;

//     printf("AES加解密的C++实现:\n");//打印标题

// loop:

//     printf("\n加密请输入: 1\n");
//     printf("解密请输入: 2\n");
//     printf("退出请输入: 0 \n\n");
//     printf("请输入选择:");
    
//     scanf("%d", &choose);
//     printf("\n");

//     switch(choose){

//     case 1:
//     	printf("请选择加密方式：\n");
//     	printf("1:AES_128_ECB,2:AES_192_ECB,3:AES_256_ECB,4:AES_128_CBC,5:AES_192_CBC,6:AES_256_CBC \n\n");
//     	printf("请输入选择:");
    	
//     	scanf("%d", &mode);
//     	printf("\n");
    	
//     	printf("请输入明文类型：\n");
//     	printf("字符串加密请输入：1\n");
//     	printf("十六进制数加密请输入：2\n");
//     	printf("二进制数加密请输入：3\n\n");
//     	printf("请输入选择:");
    	
//     	scanf("%d", &forming);
//     	printf("\n");
    	
//     	if(mode == 1 || mode == 2 || mode == 3){
//     		encrypt_ecb(S_BOX);
// 		}
		
// 		if(mode == 4 || mode == 5 || mode == 6){
//     		encrypt_cbc(S_BOX);
// 		}
    	
// //        encrypt(S_BOX);
//         goto loop;

//     case 2:
//     	printf("请选择解密方式：\n");
//     	printf("1:AES_128_ECB,2:AES_192_ECB,3:AES_256_ECB,4:AES_128_CBC,5:AES_192_CBC,6:AES_256_CBC \n\n");
//     	printf("请输入选择:");
    	
//     	scanf("%d", &mode);
//     	printf("\n");
    	
//     	printf("请选择解密结果类型：\n");
//     	printf("解密结果为字符串请输入：1\n");
//     	printf("解密结果为十六进制数请输入：2\n");
//     	printf("解密结果为二进制数请输入：3\n\n");
//     	printf("请输入选择:");
    	
//     	scanf("%d", &forming);
//     	printf("\n");
    	
//     	if(mode == 1 || mode == 2 || mode == 3){
//     		decrypt_ecb(S_BOX, N_S_BOX);
// 		}
		
// 		if(mode == 4 || mode == 5 || mode == 6){
// 			decrypt_cbc(S_BOX, N_S_BOX);
// 		}
    	
// //        decrypt(S_BOX, N_S_BOX);
//         goto loop;

//     case 0:
//         exit(0);

//     default :
//         exit(0);

//     }

//     return 0;

// }


// // 一个中文占两个字符位置 
