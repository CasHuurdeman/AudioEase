//
// Created by cashu on 05/12/2025.
//

#pragma once
#include <cmath>

typedef float T;

T PI = 4*atan(1);

/////////////////////////////////////////////////////////
// Decimation-in-freq radix-2 in-place butterfly
// data: array of Ts:
// re(0),im(0),re(1),im(1),...,re(size-1),im(size-1)
// it means that size=array_length/2 !!
//
// suggested use:
// intput in normal order
// output in bit-reversed order
//
// Source: Rabiner-Gold: Theory and Application of DSP,
// Prentice Hall,1978

void dif_butterfly(T *data,long size){

	long angle,astep,dl;
	T xr,yr,xi,yi,wr,wi,dr,di,ang;
	T *l1, *l2, *end, *ol2;

     astep=1;
	 end=data+size+size;
     for(dl=size;dl>1;dl>>=1,astep+=astep){
					  l1=data;
					  l2=data+dl;
                      for(;l2<end;l1=l2,l2=l2+dl){
							ol2=l2;
                            for(angle=0;l1<ol2;l1+=2,l2+=2){
                               ang=2*PI*angle/size;
                               wr=cos(ang);
                               wi=-sin(ang);
                               xr=*l1+*l2;
                               xi=*(l1+1)+*(l2+1);
                               dr=*l1-*l2;
                               di=*(l1+1)-*(l2+1);
                               yr=dr*wr-di*wi;
                               yi=dr*wi+di*wr;
                               *(l1)=xr;*(l1+1)=xi;
                               *(l2)=yr;*(l2+1)=yi;
                               angle+=astep;
							   }
					  }
	 }
}

/////////////////////////////////////////////////////////
// Decimation-in-time radix-2 in-place inverse butterfly
// data: array of Ts:
// re(0),im(0),re(1),im(1),...,re(size-1),im(size-1)
// it means that size=array_length/2 !!
//
// suggested use:
// intput in bit-reversed order
// output in normal order
//
// Source: Rabiner-Gold: Theory and Application of DSP,
// Prentice Hall,1978

void inverse_dit_butterfly(T *data,long size){

	long angle,astep,dl;
	T xr,yr,xi,yi,wr,wi,dr,di,ang;
	T *l1, *l2, *end, *ol2;

     astep=size>>1;
	 end=data+size+size;
     for(dl=2;astep>0;dl+=dl,astep>>=1){
					  l1=data;
					  l2=data+dl;
                      for(;l2<end;l1=l2,l2=l2+dl){
							ol2=l2;
                            for(angle=0;l1<ol2;l1+=2,l2+=2){
                               ang=2*PI*angle/size;
                               wr=cos(ang);
                               wi=sin(ang);
                               xr=*l1;
                               xi=*(l1+1);
                               yr=*l2;
                               yi=*(l2+1);
                               dr=yr*wr-yi*wi;
                               di=yr*wi+yi*wr;
                               *(l1)=xr+dr;*(l1+1)=xi+di;
                               *(l2)=xr-dr;*(l2+1)=xi-di;
                               angle+=astep;
							   }
					  }
	 }
}

/////////////////////////////////////////////////////////
// data shuffling into bit-reversed order
// data: array of Ts:
// re(0),im(0),re(1),im(1),...,re(size-1),im(size-1)
// it means that size=array_length/2 !!
//
// Source: Rabiner-Gold: Theory and Application of DSP,
// Prentice Hall,1978

void unshuffle(T *data, long size){

	long i,j,k,l,m;
	T re,im;

	//old version - turned out to be a bit slower
    /*for(i=0;i<size-1;i++){
             j=bitreverse(i,size);
             if (j>i){   //swap
                    re=data[i+i];im=data[i+i+1];
                    data[i+i]=data[j+j];data[i+i+1]=data[j+j+1];
                    data[j+j]=re;data[j+j+1]=im;
			 }
	}*/

l=size-1;
m=size>>1;
for (i=0,j=0; i<l ; i++){
	  if (i<j){
				re=data[j+j]; im=data[j+j+1];
				data[j+j]=data[i+i]; data[j+j+1]=data[i+i+1];
				data[i+i]=re; data[i+i+1]=im;
				}
	  k=m;
	  while (k<=j){
				j-=k;
				k>>=1;
				}
	  j+=k;
      }
}

/////////////////////////////////////////////////////////
// used by realfft
// parameters as above
//
// Source: Brigham: The Fast Fourier Transform
// Prentice Hall, ?

void realize(T *data, long size){

	T xr,yr,xi,yi,wr,wi,dr,di,ang,astep;
	T *l1, *l2;

	l1=data;
	l2=data+size+size-2;
    xr=*l1;
    xi=*(l1+1);
    *l1=xr+xi;
    *(l1+1)=xr-xi;
	l1+=2;
	astep=PI/size;
    for(ang=astep;l1<=l2;l1+=2,l2-=2,ang+=astep){
                               xr=(*l1+*l2)/2;
                               yi=(-(*l1)+(*l2))/2;
                               yr=(*(l1+1)+*(l2+1))/2;
                               xi=(*(l1+1)-*(l2+1))/2;
                               wr=cos(ang);
                               wi=-sin(ang);
                               dr=yr*wr-yi*wi;
                               di=yr*wi+yi*wr;
                               *l1=xr+dr;
                               *(l1+1)=xi+di;
                               *l2=xr-dr;
                               *(l2+1)=-xi+di;
	}
}

/////////////////////////////////////////////////////////
// used by inverse realfft
// parameters as above
//
// Source: Brigham: The Fast Fourier Transform
// Prentice Hall, ?

void unrealize(T *data, long size){

	T xr,yr,xi,yi,wr,wi,dr,di,ang,astep;
	T *l1, *l2;

	l1=data;
	l2=data+size+size-2;
    xr=(*l1)/2;
    xi=(*(l1+1))/2;
    *l1=xr+xi;
    *(l1+1)=xr-xi;
	l1+=2;
	astep=PI/size;
    for(ang=astep;l1<=l2;l1+=2,l2-=2,ang+=astep){
                               xr=(*l1+*l2)/2;
                               yi=-(-(*l1)+(*l2))/2;
                               yr=(*(l1+1)+*(l2+1))/2;
                               xi=(*(l1+1)-*(l2+1))/2;
                               wr=cos(ang);
                               wi=-sin(ang);
                               dr=yr*wr-yi*wi;
                               di=yr*wi+yi*wr;
                               *l2=xr+dr;
                               *(l1+1)=xi+di;
                               *l1=xr-dr;
                               *(l2+1)=-xi+di;
	}
}

/////////////////////////////////////////////////////////
// in-place Radix-2 FFT for real values
// (by the so-called "packing method")
// data: array of Ts:
// re(0),re(1),re(2),...,re(size-1)
//
// output:
// re(0),re(size/2),re(1),im(1),re(2),im(2),...,re(size/2-1),im(size/2-1)
// normalized by array length
//
// Source: see the routines it calls ...

void realfft_packed(T *data, long size){

	T *l, *end;
	T div;

	size>>=1;
	dif_butterfly(data,size);
	unshuffle(data,size);
	realize(data,size);

	end=data+size+size;
	div=size+size;
	for(l=data;l<end;l++){*l=*l/div;};
}


/////////////////////////////////////////////////////////
// in-place Radix-2 inverse FFT for real values
// (by the so-called "packing method")
// data: array of Ts:
// re(0),re(size/2),re(1),im(1),re(2),im(2),...,re(size/2-1),im(size/2-1)
//
// output:
// re(0),re(1),re(2),...,re(size-1)
// NOT normalized by array length
//
//Source: see the routines it calls ...

void irealfft_packed(T *data, long size){

	T *l, *end;
	T div;

	size>>=1;
	unrealize(data,size);
	unshuffle(data,size);
	inverse_dit_butterfly(data,size);

	end=data+size+size;
	div=size+size;
	for(l=data;l<end;l++){*l=(*l)*2*div;};
}