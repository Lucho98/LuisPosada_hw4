#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define fi 129
#define col 2
#define L 0.64
#define c 250.0
#define dt 0.00002
#define n 10000
#define pi 3.14159
void leer1(double *puntero);
void leer2(double *puntero2);
double **readMatriz( );
void solve(double **solucion);
void solve2(double **solucion2);
double **solveM();


int main(void){
	double ** u1;
	double ** u2;
	int i;
	int j;
	double *condicionesx=malloc((fi)*sizeof(double));
	leer1(condicionesx);
	double *condicionesy=malloc((fi*col)*sizeof(double));
	leer2(condicionesy);	
	u1=malloc(fi*sizeof(double*));
	for(i=0;i<=fi;i++){
		u1[i]=malloc(n*sizeof(double));
	}
	u2=malloc(fi*sizeof(double*));
	for(i=0;i<=fi;i++){
		u2[i]=malloc(n*sizeof(double));
	}
	solve(u1);
	solve2(u2);
	solveM();
		
	
	FILE *out;
	out=fopen("Resultados_hw4.txt","w");
	for (j=0;j<=128;j++){
		fprintf(out,"%f %f %f %f %f %f %f %f  %f\n",condicionesx[j],u1[j][1],u1[j][150],u1[j][450],u1[j][600],u2[j][1],u2[j][150],u2[j][450],u2[j][600]);  
	}	
	fclose(out);
	FILE *salida;
	salida=fopen("animacion_hw4.txt","w");
	for (j=0;j<=n;j+=10){
		for(i=0;i<=128;i++){
			fprintf(salida,"%f %f\n",condicionesx[i],u2[i][j]);  
		}
	}	
	fclose(salida);
	
	FILE *aud;
	aud=fopen("audio.txt","w");
	for (j=0;j<=99999;j++){
			fprintf(aud,"%f\n",u1[65][j]);  
		}	
	fclose(aud);
	

return 0;
	
}
void leer1(double* puntero){
	FILE* miarchivo;
	char* nombr="cond_ini_cuerda.dat";
	int len=2000;	
	char lineas[len];
	char *lectura; 
	miarchivo=fopen(nombr,"r");
	const char *delimiter;
	delimiter="  ";
	int i;
	for(i=0;i<129;i++){	
		fgets(lineas,len,miarchivo);
		lectura=strtok(lineas,delimiter);
		puntero[i]=atof(lectura);
		lectura=strtok(NULL,delimiter);
			
	}
		
	fclose(miarchivo);
}
void leer2(double *puntero2){
	FILE* miarchivo;
	char* nombr="cond_ini_cuerda.dat";
	miarchivo=fopen(nombr,"r");
	int i;
	double *x=malloc(fi*sizeof(double));
	double *y=malloc(fi*sizeof(double));
	for(i=0;i<129;i++){	
		 fscanf(miarchivo, "%lf %lf\n", &x[i], &y[i]);
		 puntero2[i]=y[i];
	}
	fclose(miarchivo);
}
void solve(double **solucion){
	int j;
	int i;
	double *condicionesx=malloc((fi)*sizeof(double));
	leer1(condicionesx);
	double dx=condicionesx[2]-condicionesx[1];
	double r=c*(dt/dx);
	double *condicionesy=malloc((fi*col)*sizeof(double));
	leer2(condicionesy);	
	double **u=malloc(fi*sizeof(double*));
	for(i=0;i<=fi;i++){
		u[i]=malloc(n*sizeof(double));
	}
	for(j=1;j<=(fi-1);j++){
		u[0][0]=0.0;		
		u[j][0]=condicionesy[j];
		u[j][1] =(condicionesy[j]-0.000150);
		

	}
	//metodo diferencias finitas
	for(i=1;i<=(n-1);i++){
		for(j=1;j<=(fi-1);j++){
			u[128][i]=0.0;	        		
			u[j][i+1] =(2.0*(1.0-(pow(r,2)))*u[j][i] - u[j][i-1] + pow(r,2)*(u[j+1][i] +u[j-1][i]));
			solucion[j][i]=u[j][i];
			solucion[j][0]=u[j][0];
			}
	}	

}
void solve2(double **solucion2){
	int j;
	int i;
	double *condicionesx=malloc((fi)*sizeof(double));
	leer1(condicionesx);
	double dx=condicionesx[2]-condicionesx[1];
	double r=c*(dt/dx);
	double *condicionesy=malloc((fi*col)*sizeof(double));
	leer2(condicionesy);	
	double **u=malloc(fi*sizeof(double*));
	for(i=0;i<=fi;i++){
		u[i]=malloc(n*sizeof(double));
	}
	for(j=1;j<=(fi-1);j++){
		u[0][0]=0.0;	
		u[j][0]=0.0;	
		u[j][1] =0.0; 	
	}
	//metodo diferencias finitas
	for(i=1;i<=(n-1);i++){
		for(j=1;j<=(fi-1);j++){
			u[128][i]=sin((2*pi*c*dt*i/L));
        		u[j][i+1] =(2.0*(1.0-(pow(r,2)))*u[j][i] - u[j][i-1] + pow(r,2)*(u[j+1][i] +u[j-1][i]));
			solucion2[j][i]=u[j][i];
			solucion2[j][0]=u[j][0];
			}
	}	

}
double **readMatriz( ){

   	FILE *fp;
   	fp = fopen("cond_ini_tambor.dat","r");
   	int lines=1;
   	char d;
	double **matrix;
	int i;
	int j;
    	while((d = fgetc(fp)) != EOF)
    	{
        if(d == '\n')
           lines++;
    	}
	matrix = malloc(sizeof(double *)*lines);
	for(i=0;i<lines;i++){
		matrix[i] = malloc(sizeof(double)*lines);
	}
    	fclose(fp);
    	fp = fopen("cond_ini_tambor.dat","r");
    	double m[lines][lines];

  
    
    	for(i=0;i<lines;i++){
        	for(j=0;j<lines;j++){
            		fscanf( fp, "%lf", &(m[i][j]));
        	}
        	fscanf(fp,"\n", NULL);
    	}

    	for(i=0;i<lines-2;i++){
        	for(j=0;j<lines;j++){
            		//printf("%lf ",m[i][j]);
			matrix[i][j]=m[i][j];
        	}
		printf("\n");
    	}
return matrix;
}
double** solveM(){
	int j;
	int i;
	int k;
	int w=101;
	double dx=0.5/100;
	double dtm=0.00001;
	double lam;
	lam=(pow(c,2)*pow(dtm,2))/(pow(dx,2));
	double **ini=readMatriz();
	FILE* myfile=fopen("tambor.txt","w");
	double **upa=malloc(101*sizeof(double*));
	for(i=0;i<=w;i++){
		upa[i]=malloc(101*sizeof(double));
	}
	double **upr=malloc(101*sizeof(double*));
	for(i=0;i<=w;i++){
		upr[i]=malloc(101*sizeof(double));
	}
	double **ufu=malloc(101*sizeof(double*));
	for(i=0;i<=w;i++){
		ufu[i]=malloc(101*sizeof(double));
		}
	for(i=0;i<w;i++)
	{
        	for(j=0;j<w;j++)
        	{
           		upa[i][j]=upr[i][j]=ini[i][j];
				 
        	}
        
    	}

	//metodo diferencias finitas
	for(k=1;k<n;k++)
	{
		for(i=1;i<(w-1);i++)
    		{
        		for(j=1;j<(w-1);j++)
        		{
           		ufu[i][j]=lam*(upr[i+1][j]+upr[i-1][j]-4*upr[i][j]+upr[i][j+1]+upr[i][j-1])+2*upr[i][j]-upa[i][j];
        		}
        
    		}

		for(i=1;i<(w-1);i++)
    		{
        		for(j=1;j<(w-1);j++)
        		{
           		upa[i][j]=upr[i][j];
			upr[i][j]=ufu[i][j];
        		}
		}
		if(k == 2 |k == (n/2) | k == (n/4) | k == (n/8)| k == (n-1))
		{
	        	for (i=0; i<w; i++)
			{
				for(j=0;j<w;j++)
				{
					fprintf(myfile, "%f ", upr[i][j]);
				
		        	}
				fprintf(myfile, "\n");	
			}
		}	

	}

}


