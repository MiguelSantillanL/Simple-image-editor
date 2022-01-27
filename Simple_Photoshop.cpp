#include "Simple_Photoshop.hpp"

#define RGB(R,G,B) ( (R*0.3) + (G*0.59) + (B* 0.11) )
#define Promedio_M(sum,n) ( sum/(n*n) )  
#define F_Seno(Angle_Rot) (sin(-Angle_Rot*M_PI /180))
#define F_Coseno(Angle_Rot) (cos(-Angle_Rot*M_PI /180))
#define var_x(xt,coseno,yt,seno,nrows) (int(float(xt)*coseno-float(yt)*seno)+nrows)
#define var_y(xt,seno,yt,coseno,ncol) (int(float(xt)*seno+float(yt)*coseno)+ncol)

int Process_Pic(){//tiene que ser int para el return -1
	int **M_Pic;
	int rows = 0, col = 0;
    // carga la imagen a color
	Mat Color_Pic = imread("Imagen.jpg");
	//obtencion de valores para rows y col
	rows = Color_Pic.rows;
	col = Color_Pic.cols;
    // verificar si la imagen ha sida cargada correctamente
    if (Color_Pic.empty()){
        printf("No se ha cargado la imagen \n");
		return -1;
    }
	else{
		cout << "La imagen es de " << col << " x " << rows << endl;
		float **R,**G,**B,MTemp = 0.0;
		M_Pic=CrearMatriz(rows,col);
        //Guardamos el Valor R-G-B en una matriz diferente
		R=CrearMatrizfloat(rows,col);   R=GetRGB(rows,col,2,Color_Pic);
		G=CrearMatrizfloat(rows,col);	G=GetRGB(rows,col,1,Color_Pic);
		B=CrearMatrizfloat(rows,col);	B=GetRGB(rows,col,0,Color_Pic);

        // Color a Escala de Grises
		for (int i = 0; i < rows; i++){
				for (int j = 0; j < col; j++){
						//MTemp = (R[i][j] * 0.3) + (G[i][j] * 0.59) + (B[i][j] * 0.11);
						MTemp = RGB( R[i][j], G[i][j], B[i][j]);
						//MTemp = (R+G+B)/3;
						M_Pic[i][j] = int(MTemp);
					}
			}
            
	Image_Grayscale(M_Pic,rows,col);
	int opc1;
	cout << "La imagen fue pasada a escala de grises" << endl;
	cout << "Que desea hacer?" << endl;
	cout << "  1.-Agrandar imagen  \n  2.-Reducir imagen \n  3.-Rotar imagen"<< endl;
	cin >> opc1;
	if(opc1==1){
		Max_Image(M_Pic,rows,col);  }
	else if(opc1==2){
		Min_Image(M_Pic,rows,col);  }
	else if(opc1==3){
        Rot_Image(M_Pic,rows,col);  }

	LiberarMemoria(M_Pic,rows,col);
	LiberarMemoriafloat(R,rows,col);
	LiberarMemoriafloat(G,rows,col);
	LiberarMemoriafloat(B,rows,col);
    waitKey(0);
	}
	return 0;
}

//Transforma la imagen de color a escala de grises
float **GetRGB(int rows,int col,int RGBopc, Mat Color_Pic){
    //RGBopc -> COLOR QUE QUEREMOS  (R,G,B)
	float **RGB;
	RGB=CrearMatrizfloat(rows,col);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++)
            RGB[i][j]=Color_Pic.data[Color_Pic.channels()*(Color_Pic.cols*i + j) + RGBopc]; //Sin usar <Vec3b>
			//RGB[i][j] = ImagenColor.at<Vec3b>(i, j)[RGBopc];    //Usando <Vec3b>
	return RGB;
	LiberarMemoriafloat(RGB,rows,col);
}

//Guarda la Imagen en escala de grises un .pgm (se puede omitir)
void Image_Grayscale(int **M_Pic,int rows,int col)
{
	FILE* Grayscale;
	
	Grayscale = fopen("Imagen_Grayscale.pgm", "wb");
	fprintf(Grayscale, "P2\n");
	fprintf(Grayscale, "%d %d\n", col, rows);
	fprintf(Grayscale, "255\n");
	int temp = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < col; j++) {
			temp = M_Pic[i][j];
			// escala de grises del arreglo al archivo
			fprintf(Grayscale, "%d ", temp);
		}
		fprintf(Grayscale, "\n");
	}
	fclose(Grayscale);
}


void Max_Image(int **M_Pic,int rows,int col){
    int **M_Resize;
    int n,nrows,ncol;
    cout << "ingrese escalado" << endl;
    cin  >> n;
    nrows=rows*n;
    ncol=col*n;
	M_Resize=CrearMatriz(nrows,ncol);
    for(int i=0 ; i<rows ; i++){
		for(int j=0 ; j<col ; j++){
			//2 for internos para la matriz copia
			for(int k=(n*i) ; k<((n*i)+n) ; k++){
					for(int l=(n*j) ; l<((n*j)+n) ; l++){
						M_Resize[k][l]=M_Pic[i][j]; }
			}
        }
	}
    cout << nrows << " x " << ncol << endl;
	FILE* Escala;
	Escala = fopen("Imagen_Escalada.pgm", "wb");
	fprintf(Escala, "P2\n");
	fprintf(Escala, "%d %d\n", ncol, nrows);
	fprintf(Escala, "255\n");
	int temp = 0;
	for (int i = 0; i < (nrows); i++) {
		for (int j = 0; j < (ncol); j++) {
			temp = M_Resize[i][j];
			// escala de grises del arreglo al archivo
			fprintf(Escala, "%d ", temp);
		}
		fprintf(Escala, "\n");
	}
	fclose(Escala);
}


void Min_Image(int **M_Pic,int rows,int col){
    int **M_Resize;
    int n,nrows,ncol;
    cout << "ingrese el numero a reducir" << endl;
    cin  >> n;
    //se reduce el tamaño en n
    nrows=int(float(rows)/float(n));
    ncol=int(float(col)/float(n));
    cout << nrows << " x " << ncol << endl;
	M_Resize=CrearMatriz(nrows,ncol);
    for(int i=0 ; i<nrows ; i++){
		for(int j=0 ; j<ncol ; j++){
			//2 for internos para la matriz copia
			int sum=0;
			float prom=0.0;
			for(int k=(n*i) ; k<((n*i)+n) ; k++){
					for(int l=(n*j) ; l<((n*j)+n) ; l++){
						sum += M_Pic[k][l];
						//cout << "suma= " <<sum << endl;
					}
				}
            //se hace un promedio de los cuadros alrededor para no perder calidad
            //prom=float(sum)/(float(n*n));           
			prom  = Promedio_M(float(sum),float(n));  
                 
            // cout << "promedio= " << prom << endl;
            M_Resize[i][j]=int(prom);
		}
	}
	FILE* Escala;
	Escala = fopen("Imagen_Reducida.pgm", "wb");
	fprintf(Escala, "P2\n");
	fprintf(Escala, "%d %d\n", ncol, nrows);
	fprintf(Escala, "255\n");
	int temp = 0;
	for (int i = 0; i < (nrows); i++) {
		for (int j = 0; j < (ncol); j++) {
			temp = M_Resize[i][j];
			// escala de grises del arreglo al archivo
			fprintf(Escala, "%d ", temp);
		}
		fprintf(Escala, "\n");
	}
	fclose(Escala);
}

void Rot_Image(int **M_Pic,int rows,int col)
{
    float Angle_Rot;
    int x,y;
    int **M_Rot;
    int MNrows,MNcol;
    cout << "A cuantos grados desea rotar la imagen? ";
    cin >>Angle_Rot;

    //Dimensiones de la matriz rotada
    MNrows=rows;
    MNcol=col;
 
    M_Rot=CrearMatriz(MNrows,MNcol);
	float seno,coseno;
    for(int i=0; i<MNrows ; i++){
        for(int j=0 ; j<MNcol ; j++){
            int nrows = MNrows*0.5;
			int ncol = MNcol*0.5;
			int xt = i - nrows;
			int yt = j - ncol;

			//float seno=sin(-Angle_Rot*M_PI /180);
			seno = F_Seno(Angle_Rot);
			//float coseno=cos(-Angle_Rot*M_PI /180);
			coseno = F_Coseno(Angle_Rot);

			//x=int(float(xt)*coseno-float(yt)*seno)+nrows;
			//y=int(float(xt)*seno+float(yt)*coseno)+ncol;

			x = var_x(xt,coseno,yt,seno,nrows);
			y = var_y(xt,seno,yt,coseno,ncol);
           
            if((x>=0) && (y>=0) &&(x<MNrows)&&(y<MNcol)) //guardamos valores de la imagen
                M_Rot[i][j]=M_Pic[x][y];
            else //si no hay valres se va a rellenar de color blanco
                M_Rot[i][j]=255;
        }
    }

    FILE* Rotada;
	Rotada = fopen("Imagen_Rotada.pgm", "wb");
	fprintf(Rotada, "P2\n");
	fprintf(Rotada, "%d %d\n", MNcol,MNrows);
	fprintf(Rotada, "255\n");
	int temp = 0;
	for (int i = 0; i < (MNrows); i++) {
		for (int j = 0; j < (MNcol); j++) {
			temp = M_Rot[i][j];
			// escala de grises del arreglo al archivo
			fprintf(Rotada, "%d ", temp);
		}
		fprintf(Rotada, "\n");
	}
	fclose(Rotada);
}