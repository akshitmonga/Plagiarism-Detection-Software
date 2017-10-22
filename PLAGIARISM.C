#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>

void computeLPSArray(char *pat, int M, int *lps);
int maxx(int a,int b);
int line_length[50];
int count=0;
int threshold=50;
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char* X, char* Y, int m, int n )
{
   if (m == 0 || n == 0)
     return 0;
   if (X[m-1] == Y[n-1])
     return 1 + lcs(X, Y, m-1, n-1);
   else
     return maxx(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
}

/* Utility function to get max of 2 integers */
int maxx(int a, int b)
{
    return (a > b)? a : b;
}

int KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i,z;

    // create lps[] that will hold the longest prefix suffix values for pattern
    int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // index for pat[]

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    for(z=0;z<M;z++)
	printf("%d  ",lps[z]);

    i = 0;  // index for txt[]
    while (i < N)
    {
      if (pat[j] == txt[i])
      {
	j++;
	i++;
      }

      if (j == M)
      {
	printf("Found pattern at index %d \n", i-j);
	return ( i - j );
      }

      // mismatch after j matches
      else if (i < N && pat[j] != txt[i])
      {
	// Do not match lps[0..lps[j-1]] characters,
	// they will match anyway
	if (j != 0)
	 j = lps[j-1];
	else
	 i = i+1;
      }
    }
    free(lps); // to avoid memory leak
    return 0;
}

void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;  // lenght of the previous longest prefix suffix
    int i;

    lps[0] = 0; // lps[0] is always 0
    i = 1;

    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
	 len++;
	 lps[i] = len;
	 i++;
       }
       else // (pat[i] != pat[len])
       {
	 if (len != 0)
	 {
		len = lps[len-1];

	   // Also, note that we do not increment i here
	 }
	 else // if (len == 0)
	 {
	   lps[i] = 0;
	   i++;
	 }
       }
    }
}

int search(char *pat , char *txt, int q,int d )
{	int M=strlen(pat);
	int N=strlen(txt);
	int i,j;
	int p=0;		//hash value fp1
	int t=0;		//hash value fp2
	int h=1;
	 for (i = 0; i < M-1; i++)
	h = (h*d)%q;
	 for (i = 0; i < M; i++)
    {
	p = (d*p + pat[i])%q;
	t = (d*t + txt[i])%q;
    }
	  for (i = 0; i <= N - M; i++)
    { if ( p == t )
	{
	    /* Check for characters one by one */
	    for (j = 0; j < M; j++)
	    {
		if (txt[i+j] != pat[j])
		    break;
	    }
	    if (j == M)  // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
	    {
		printf("Pattern found at index %d \n", i);
		return i;
	    }
	}

	// Calculate hash value for next window of text: Remove leading digit,
	// add trailing digit
	if ( i < N-M )
	{
	    t = (d*(t - txt[i]*h) + txt[i+M])%q;

	    // We might get negative value of t, converting it to positive
	    if(t < 0)
	      t = (t + q);
	}
    }
    return 0;
	}
char** read_lines(FILE* txt, int* count)
{
    char** array = NULL;        /* Array of lines */
    int    i;                   /* Loop counter */
    char   line[1000];           /* Buffer to read each line */
    int    line_count;          /* Total number of lines */
    /* Clear output parameter. */
    *count = 0;
    /* Get the count of lines in the file */
    line_count = 0;
    while (fgets(line, sizeof(line), txt) != NULL)
    {
       line_count++;
    }
    /* Move to the beginning of file. */
    rewind(txt);
    /* Allocate an array of pointers to string*/
    array = malloc(line_count * sizeof(char *));
    if (array == NULL) {
    return NULL;
    }
    /* Read each line from file and deep-copy in the array. */
    for (i = 0; i < line_count; i++)
    {
	/* Read the current line. */
	fgets(line, sizeof(line), txt);
	/* Remove the ending '\n' from the read line. */
	line_length[i] = strlen(line);
	line[line_length[i] - 1] = '\0';
	line_length[i]--; /* update line length */
	/* Allocate space to store a copy of the line. +1 for NUL terminator */
	array[i] = malloc(line_length[i] + 1);
	/* Copy the line into the newly allocated space. */
	strcpy(array[i], line);
    }
    *count = line_count;
    return array;
}

void index()
{
	int gdriver=DETECT,gmode;
	int midx, midy;
	int i,count,adn;
	float octave[7]={130.81,146.83,164.81,174.61,196.220,246.94};

	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");

	setbkcolor(0);
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;

	while(!kbhit())
	{
		adn=random(7);
		sound(octave[adn]*10);
		delay(190);
		nosound();
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
		setcolor(8);
		outtextxy(midx,midy,"ALGORITHMS");
		settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
		outtextxy(midx,midy+30,"project");
	}

	cleardevice();

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
	setcolor(YELLOW);
	outtextxy(midx,midy,"PLAGIARISED");
	delay(300);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(YELLOW);
	outtextxy(midx,midy+80,"LOADING . . .");
	setcolor(8);
	rectangle(midx-100,midy+100,midx+100,midy+115);
	setfillstyle(1,YELLOW);
	i=midx-98;
	for(count=0;count<25;count++)
	{
		bar(i,midy+102,i+6,midy+113);
		adn=random(7);
		sound(octave[adn]*10);
		delay(200);
		nosound();
		i=i+8;
	}
	setfillstyle(1,15);
	bar(midx-100,midy+100,midx+100,midy+115);
	bar(midx-52,midy+60,midx+100,midy+100);
	setcolor(3);
	outtextxy(midx,midy+80,"PRESS ANY KEY TO CONTINUE");
	setcolor(15);
	settextjustify(LEFT_TEXT, RIGHT_TEXT);
	cleardevice();
	getch();
	closegraph();
}

int main()
{
	int gdriver=DETECT,gmode,choice;
	char restart;
	char** array =NULL;
	FILE* file,*fp;
	char filename[9000];
	char fname1[9000];
	int i,res,p,j;
	int line_count;
	int per=0,c ;
	int ka;
	clrscr();
	index();
	initgraph(&gdriver,&gmode,"C:\\turboc3\\BGI");
	clrscr();
	do{
		label:clrscr();
		cleardevice();
		printf("\n\n\t\t\tPLAGIARISED : CHECKER SYSTEMS\n");
		printf("\t___________________________________________________\n\n");
		printf("\n\n\n\t1 -> KMP ALGORITHM");
		printf("\n\n\t2 -> LCS ALGORITHM");
		printf("\n\n\t3 -> RABIN KARP ALGORITHM");
		printf("\n\n\t4 -> EXIT");
		printf("\n\n\n\n\n\t\tPlease provide your input here <1-4> : ");
		scanf("%d",&choice);
		clrscr();
		printf("Enter file1 name :");
					scanf("%s",&filename);
				printf("Enter file2 name:");
					scanf("%s",&fname1);
				file = fopen(filename, "rt");
				fp=fopen(fname1,"rt");
				if (file == NULL) {
				printf("Can't open file %s.\n", filename);
				exit(1);
							}
				else if(fp==NULL)
				{
					printf("Can't open file %s.\n",fname1);
					exit(1);
    }
    while(!feof(fp))
    {
    res=fread(fname1,1,(sizeof fname1)-1,fp);
    fname1[res]=NULL;
    printf("%s",fname1);
    }
    fname1[strlen(fname1)] = '\0';
    /* Read lines from file. */
    array = read_lines(file, &line_count);
    switch(choice)
	   {
	  case 1 :
	  {

    /* print out the read lines. */
    for (i = 0; i < line_count ; i++)
    {
	printf("\n[%d]: %s\n", (i+1), array[i]);
	c = KMPSearch( array[i] , fname1 );
	count=(strlen(fname1) - c) ;
	per+=((count)*100/strlen(fname1));
       //	printf("\nPercentage matching is = %d",per);
       //	puts("");
	//printf("%d\n",line_count);

       //	printf("\nTotal matched subsequence length = %d",count);

    }
	setbkcolor(BLACK);
	//per = ((count)*100/strlen(fname1));
	printf("\nTotal matched subsequence length = %d",count);
	ka=per/line_count;
	printf("\nPercentage matching is = %d",ka);
	if(ka>threshold)
	printf("\nSimilar\n");
	else
	printf("\nNot Similar\n");
	break;
    } // case
    case 2:
    {
    for (i = 0; i < line_count ; i++)
    {
	printf("\n[%d]: %s\n", (i+1), array[i]);
	count += lcs( array[i] , fname1 , strlen(array[i]) , strlen(fname1));
    }
    setbkcolor(BLACK);
    per = (count*100/strlen(fname1));
	printf("\nTotal matched subsequence length = %d",count);
	printf("\nPercentage matching is = %d",per);
	if(per>threshold)
	printf("\nSimilar\n");
	else
	printf("\nNot Similar\n");
	break;
    }
    case 3:
    {
	for (i = 0; i < line_count ; i++)
	{
	printf("\n[%d]: %s\n", (i+1), array[i]);
	c = search( array[i] , fname1,101,10 );
	count=(strlen(fname1) - c) ;
	per+=((count)*100/strlen(fname1));
	//count = count + (strlen(fname1) - c) ;
    }
    setbkcolor(BLACK);
	per = (strlen(fname1)*100/count);
	printf("\nTotal matched subsequence length = %d",count);
	ka=per/line_count;
	printf("\nPercentage matching is = %d",ka);
	if(ka>threshold)
	printf("\nSimilar\n");
	else
	printf("\nNot Similar\n");
	break;
    }
			case 4:exit(1);
				break;
			default:printf("\n\n\nERROR : INPUT AGAIN");
				goto label;
		}
		printf("\n\n\n\nDO YOU WANT TO GO TO CONTINUE OR EXIT (Y/N) ? ");
		flushall();
		scanf("%c",&restart);

	}while(restart=='y'||restart=='Y');
	fclose(file);
    fclose(fp);
    for (i = 0; i < line_count; i++)
    {
	free(array[i]);
    }
    free(array);
    array = NULL;
	getch();
	clrscr();
	return 0;
}