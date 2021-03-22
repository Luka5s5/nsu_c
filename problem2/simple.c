#include <stdio.h>
#include <assert.h>

#define MXRE 64
#define MXS 1024
#define MXNUMLEN 10
//#define and &&
//#define or ||
//#define bool int

int pow10[10];
void fill(){
	pow10[0]=1;
	for(int i=1;i<10;i++)
		pow10[i]=pow10[i-1]*10;
}

bool is_D(char ch){
	return ('A'<=ch and ch<='Z') or ('a'<=ch and ch<='z');
}

bool is_d(char ch){
	return '0'<=ch and ch<='9';
}


int strlen(char *s){
	int i=-1;
	while(s[++i]);
	return i;
}

int b_pow(int a, int n){
	if(n==0) return 1;
	if(n==1) return a;
	if(n&1){
		return(b_pow(a,n-1)*a);
	}
	else{
		int t=b_pow(a,n>>1);
		return t*t;
	}
}


// Наверное, стоило как-то выделить парсер отдельно но тут вроде всё +-просто парсится

bool is_match(char *t, char *re, int lt, int rt, int lre, int rre){
	if(lt==rt)
		return (lre==rre);
	if(lre>rre)
		return 0;
	if(re[lre]=='\\'){
		assert(!(lre+1>=rre));
		assert(!(re[lre+1]!='d' && re[lre+1]!='D'));

		if((re[lre+1]=='d' and !is_d(t[lt])) or (re[lre+1]=='D' and !is_D(t[lt])))
			return 0;
		return is_match(t,re,lt+1,rt,lre+2,rre);
	}

	if(is_d(re[lre]) or is_D(re[lre])){
		if(re[lre]==t[lt])
			return is_match(t,re,lt+1,rt,lre+1,rre);
		else
			return 0;
	}

	if(re[lre]=='~'){
		if(re[lre+1]!=t[lt]){
			return is_match(t,re,lt+1,rt,lre+2,rre);
		}
		else
			return 0;
	}
	if(re[lre]=='['){
		int n=0;
		int last=lre;
		while(is_d(re[++last]));
		for(int i=last-1, pw=1; i>lre; i--, pw*=10)
			n+=pw*(re[i]-'0');
		int lbracket=last+1;
		int rbracket=lbracket;
		int escs=0;
		while(((escs+=re[rbracket]=='\\') or 1) and (re[++rbracket]!=')'));
		//printf("found a shit from %d to %d with n=%d\n",lbracket,rbracket,n);
		int letters=(rbracket-lbracket-1) - escs;
		bool ans=1;
		if(rt-lt<letters*n) return 0;

		for(int i=0;i<n;i++){
			//printf("letters:%d t=[ %d(%c); %d(%c) ], re=[ %d(%c); %d(%c) ] ans is now: ",letters,lt+i*letters,t[lt+i*letters], lt+(i+1)*letters-1,t[lt+(i+1)*letters-1],lbracket+1,re[lbracket+1],rbracket-1,re[rbracket-1]);
			ans&=is_match(t,re,lt+i*letters,lt+(i+1)*letters,lbracket+1, rbracket);
			//printf("%d\n",ans);
		}

		if(!ans) return 0;
		//printf("[] is ok, checking t=[ %d(%c); %d(%c) ], re=[ %d(%c); %d(%c) ]\n", lt+(n)*letters,t[lt+(n)*letters], rt-1,t[rt-1], rbracket+2, re[rbracket+2], rre-1, re[rre-1]);
		return is_match(t,re,lt+(n)*letters,rt,rbracket+2,rre);
	}
}

int main(){
	/**/
	fill();
	char re[MXRE], s[MXS];
	int t,n,m;
	scanf("%s",re);
	n=strlen(re);
	scanf("%d",&t);

	bool any=0;
	for(int i=0;i<t;i++){
		scanf("%s",s);
		m=strlen(s);
		//printf("Parsing %s, num:%d\n",s,i);
		bool ans=is_match(s,re,0,m,0,n);
		if(ans)
			printf("%d ",i);
		any|=ans;
	}

	if(!any)
		printf("none");
	/**/
}
