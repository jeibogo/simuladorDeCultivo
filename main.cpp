#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

int main(){

    ifstream elArchivo;
    string texto;

    int cuentaLoop=0;

 elArchivo.open("matrizCultivos.csv",ios::in);//se abre el archivo en modo lectura

    if(elArchivo.fail()){//si no se encuentra el archivo mandar mensaje
        
        cout<<"No se encontro el archivo"<<endl;
        exit(1);
    }

    int cantidadCol=0;

    vector< vector<string> >titulos; //cuando se corten las palabras de aux por la coma en el 'if(aux[i]){...}' se gruardaran aqui
    vector<string> caracteres; //obtiene caracter por caracter a aux que sirve solo para saber cantidad de columnas, ahora hay que cortar esa palabras
    string aux; // guarda la primera linea de la tabla csv es decir los titulos.

    getline(elArchivo,aux);
    for(int i=0; i<aux.size(); i++){

        if(aux[i] == ','){

            cantidadCol += 1;
        }

    }
    



    //NO ESTA FUNCIONANDO
   // string columna;  // mientras tanto, para obtener lo nombres de las columnas
    //vector<string> titulo; //guarda el nombre de las columnas en un vector
    //while( !aux.empty() ){
    
   //     getline(aux,columna,',');
   //     titulo.push_back(columna);
   // }
    //NO ESTA FUNCIONANDO

    cout<<aux;

    cout<<cantidadCol<<" = cantidad de columnas"<<endl;
    
    vector < vector<string> > matriz;

    int comas = 0;//cuenta cuantas comas van. 
    vector <string> tupla;   // tupla por fuera para reiniciarla luego, no cada while

    string word;
    while (!elArchivo.eof()){

        comas += 1;

        getline(elArchivo,word,',');//va metiendo cada cadena de el archivo en variable word

        tupla.push_back(word); //metre la cadena en tupla, que es un vecor
        

        if(comas%5 == 0){   //con 5 comas se sabe que ya paso la primera linea

            matriz.push_back(tupla);     //se guarda el vector en otro vector llamado matriz

            while(tupla.empty() == false){ //se vacia tupla para volverse a usar. pues si no , estariamos sobreescribiendo
                tupla.pop_back();
            }
            
        }
        
    }

    cout<<matriz.size()<<endl;
    cout<<matriz[1].size()<<endl;

    //IMPRIMIR LA MATRIZ?
    for (int i =0; i<matriz.size(); i++){

        for(int j=0; j<matriz[i].size(); j++){ 

            cout<<" "<<matriz[i][j];
        }
        cout<<endl;
    }

    cout<<matriz[3][4];

    //TOMAR DATOS DEL USUARIO
    
    vector<string> datosUsuarioMax;
    vector<string> datosUsuarioMin;

   for(int p=0; p<cantidadCol-2; p++){  //empieza en 1 para hacer solo 4 veces ya que no se requiere poner la columna del cultivo

        cout<<"p en el que estamos"<<p<<endl;

        if(p == 0){ //si p es 0 entonces hacer la primera columna que seria textutra

            bool flagSalir=0;

            while(flagSalir==0){
                
                cout<<"Elija el tipo de textura que predomina:"<<endl;
                cout<<"1. arenoso"<<endl;
                cout<<"2. arcilloso"<<endl;
                cout<<"3. limoso"<<endl;

                string opc;
                cin>>opc;               

                if(opc=="1"){

                    datosUsuarioMax.push_back("arenoso");   //todas la texturas estaran comparadas con datosusuarioMax[0]
                    datosUsuarioMin.push_back("arenoso");  
                    flagSalir=1;
                }
                else if(opc=="2"){
                    
                    datosUsuarioMax.push_back("arcilloso");
                    datosUsuarioMin.push_back("arcilloso");
                    flagSalir=1;
                }
                else if(opc=="3"){
                    
                    datosUsuarioMax.push_back("limoso");
                    datosUsuarioMin.push_back("limoso");
                    flagSalir=1;
                }else{

                   cout<<"No ha elegido una opcion"<<endl;
                }
            }
        }

         //no se sabe porque pero esta imprimiendo una vez de mas, hay que corregir con un -2.

        cout<<"escriba minimo valor registrado para el PH"<<endl; //eso que dice pH hay que volverlo automatico y ponerle restricciones.                             
        string x;
        cin>>x;

        cout<<"escriba maximo valor registrado para el PH"<<endl;
        string y;
        cin>>y;
        //pasar a double, para poder comparar

        double a = stod(x);
        double b = stod(y);

        if(a<b){

            datosUsuarioMin.push_back(x);
            datosUsuarioMax.push_back(y);
            }else{
            datosUsuarioMin.push_back(y);
            datosUsuarioMax.push_back(x);
        }
        
        

        
    }

    //VER DATOS USUARIO

    for(int a=0; a<datosUsuarioMax.size(); a++ ){

        cout<<datosUsuarioMax[a]<<" ";
    }
    cout<<endl;
    for(int b=0; b<datosUsuarioMin.size(); b++){

        cout<<datosUsuarioMin[b]<<" ";
    } 
    cout<<endl;

    //COMPARANDO LOS DATOS DE EL CSV CON LOS DEL USUARIO. 

    for(int u=0; u<matriz.size(); u++){

            for(int n =1 ; n<datosUsuarioMax.size()+1; n++){ // como matriz es mas grande, hay que mover los datos de usuario que es un vector mas pequeño empezamos desde 1 para no tomar en cuenta la columna cultivo de la matriz y sumamos 1 para poder comparar e imprimir todo.

                //cout<<"estamos en la n ====="<<n<<endl;

                //para guiarse en la ejecucion (el debug casero)
                
                //cout<<matriz[u][n] << "MATRIZ"<<endl;
                //cout<<datosUsuarioMin[n-1]<< "MIN"<<endl;
                //cout<<datosUsuarioMax[n-1]<< "MAX"<<endl;

                if(n<2){ //si n no ha pasado de la parte donde se selecciona la textura de suelo se usa una comparacion simple con datosUsuario max
                    
                    cout<<matriz[u][0];

                    if( datosUsuarioMin[n-1] == matriz[u][n] ){
                        
                        cout<<" O";
                    } 
                    else{
                        cout<<" X";
                    }
                
                }else{ //si ya paso la parte de textura, hay que cambiar los string a double con la libreria sstring y la funcion stringstream
                     
                     double min, mid, max;

                    stringstream(datosUsuarioMin[n-1])>>min;
                    stringstream(matriz[u][n])>>mid;
                    stringstream(datosUsuarioMax[n-1])>>max;

                    if( (min - mid) <= 0 && (max - mid) >= 0 ){
                        
                        cout<<" O";
                    } 
                    else{
                        cout<<" X";
                    }

                }
              
            }

            cout<<endl;
        
    }

    return 0;

}
