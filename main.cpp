#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//FUNCIONES
string cadenaNumero(string x, int datoTitulo){

    bool esNumeroSalir=0;
  
    int i = 0;

    while( esNumeroSalir == 0){

          bool alfabeto=0;
          int contadorPunto=0;
          int contadorSigno=0;

          for(int j=0; j<x.size(); j++){ //recorre el string en busqueda de puntos
                
                if( x[j] == ',' || x[j] =='.'){ //si se escribio una coma la cambia a punto

                    x[j] = '.';
                        
                    contadorPunto += 1; 
                }

                if(x[j] == '-' ){

                    contadorSigno += 1; //por si acaso los negativos
                }
            
            }


            //cout<<contadorPunto<<"punto";
            //cout<<contadorSigno<<"signo";

            if( x == ".-"|| x == "-."){ //una forma de dañar el programa sin que salten errores.

                x = "error";//error es solo una palabra que se eligio para que no pase el filtro, ya el filtro va a saber que no es un numero
            }

           if(contadorPunto == 1 && x.size() == 1){ //por si acaso es solo un punto
               x = "0";
           }
           if(contadorSigno == 1 && x[0]!='-'){
               
               contadorSigno +=1; //con esto se asegura que no pase el filtro de si es negativo al tener un solo '-', el problemas es que esta en una posicion indevida
           }

          //si s un numero o punto o coma y no se contaron mas de 1 punto (contando el 1), se tiene una letra o no. 
        for(int i = 0; i<x.size(); i++){ 

            if( (x[i] == '1' || x[i] == '2' || x[i] == '3' || x[i] == '4' || x[i] == '5' || x[i] == '6' || x[i] == '7' || x[i] == '8' || x[i] == '9' || x[i] == '0' || x[i] =='.' || x[i]==',' || x[i] == '-') && contadorPunto <= 1 && contadorSigno <=1 ){
                

                //no hace falta hacer nada, simplemente esta bien, y el caracter en el que estamos es un numero     
            }else{
                alfabeto = 1;
            }
        }
        if(alfabeto == 1){

            cout<<"el numero debe ser un entero o decimal"<<endl;
            cin>>x;

        }else{
            
            esNumeroSalir=1;

        }

    }

    //RESTRICCIONES SEGUN LA COLUMNA
    double paraComparar;
    stringstream(x) >>paraComparar;

    if(datoTitulo == 2){ //estamos en pH

        

        if(paraComparar < 0){
            x = "0";
        }
        else if(paraComparar>14){
            
            x ="14";
        }
    }
    else if(datoTitulo == 3){ // temperatura minima en celcius -273
        
        if(paraComparar < -273.15){
            x = "-273.15";
        }
        
    }else if(datoTitulo == 4){//milimetros de precipitacion

        if(paraComparar<0){
            x="0";
        }
    }
    
    return x;
}


//INICIO
int main(){
    
    cout<<"--------------------------"<<endl;
    cout<<"<< SIMULADOR DE CULTIVO >>"<<endl;
    cout<<"--------------------------"<<endl;

    ifstream elArchivo;
    string texto;

    int cuentaLoop=0;
//ABRIR EL ARCHIVO CSV Y VER SI NO TIENE FALLOS. EL CSV DEBE TENER PUNTOS EN VEZ DE COMAS EN DECIMAL. ADEMAS PONER UNA COMA DESPUES DE CADA FIN DE LINEA-
 elArchivo.open("matrizCultivos.csv",ios::in);//se abre el archivo en modo lectura

    if(elArchivo.fail()){//si no se encuentra el archivo mandar mensaje
        
        cout<<"No se encontro el archivo"<<endl;
        exit(1);
    }

    int cantidadCol=0;

    //vector< vector<string> >titulos; //cuando se corten las palabras de aux por la coma en el 'if(aux[i]){...}' se gruardaran aqui
    vector<string> titulo; //obtiene caracter por caracter a aux que sirve solo para saber cantidad de columnas, ahora hay que cortar esa palabras
    string aux; // guarda la primera linea de la tabla csv es decir los titulos.

    getline(elArchivo,aux);
    string palabra;
    
    //SEPARA LAS PALABRAS DE AUX Y DICE CUANTAS COLUMNAS TIENE EL CSV
    for(int i=0; i<aux.size(); i++){//obtiene caracter a caracter de los titulos y los guarda en vector titulos

        if(aux[i] != ','){
        
            palabra.push_back(aux[i]);
            
        }
        else{
            
            titulo.push_back(palabra);

            while(palabra.empty()==false){
                
                palabra.clear();
            }

            cantidadCol += 1;
        }

    }
    

    //cout<<cantidadCol<<" = cantidad de columnas"<<endl; DEBUG
    
    vector < vector<string> > matriz;

    int comas = 0;//cuenta cuantas comas van. 
    vector <string> tupla;   // tupla por fuera para reiniciarla luego, no cada while

    string word;

    //PASAR LOS DATOS DEL CSV A LA MATRIZ
    while (!elArchivo.eof()){

        comas += 1;

        getline(elArchivo,word,',');//va metiendo cada cadena de el archivo en variable word

        tupla.push_back(word); //metre la cadena en tupla, que es un vecor
        

        if(comas%cantidadCol == 0){   //con 5 comas se sabe que ya paso la primera linea

            matriz.push_back(tupla);     //se guarda el vector en otro vector llamado matriz

            while(tupla.empty() == false){ //se vacia tupla para volverse a usar. pues si no , estariamos sobreescribiendo
                tupla.pop_back();
            }
            
        }
        
    }

    //cout<<matriz.size()<<endl; DEBUG
    //cout<<matriz[1].size()<<endl; DEBUG

    //IMPRIMIR LA MATRIZ? DEBUG
    //for (int i =0; i<matriz.size(); i++){

      //  for(int j=0; j<matriz[i].size(); j++){ 

        //    cout<<matriz[i][j].substr(0,7)<<"\t";
        //}
       // cout<<endl;
   // }

    vector<string> datosUsuarioMax;
    vector<string> datosUsuarioMin;

//TOMAR DATOS DEL USUARIO
//int p=0; p<cantidadCol-2; p++ recordatorio de como estaba el loop
   for(int p=1; p<cantidadCol; p++){  //empieza en 1 para hacer solo 4 veces ya que no se requiere poner la columna del cultivo

        //cout<<"p en el que estamos"<<p<<endl; DEBUG

        if(p == 1){ //si p es 0 entonces hacer la primera columna que seria textutra

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
        
        }else{

                //no se sabe porque pero esta imprimiendo una vez de mas, hay que corregir con un -2.

                cout<<"escriba minimo valor registrado para "<<titulo[p]<<endl; //eso que dice pH hay que volverlo automatico y ponerle restricciones.                             

                string datoMin;
                cin>>datoMin;
                //si sirve como numero decimal, se usa y se asigna. la funcion obliga a 
                datoMin = cadenaNumero(datoMin,p);
                double a; //a es para comparar y ver cual es el verdadero min y max en caso de haberlos colocado al reves.

                stringstream(datoMin) >> a;

                cout<<"escriba maximo valor registrado para "<<titulo[p]<<endl;
                string datoMax;
                cin>>datoMax;
                datoMax = cadenaNumero(datoMax,p);

                //pasar a double, para poder comparar
                double b;
                stringstream(datoMax) >> b;

                if(a<b){

                    datosUsuarioMin.push_back(datoMin);
                    datosUsuarioMax.push_back(datoMax);
                }
                else{
                
                    datosUsuarioMin.push_back(datoMax);
                    datosUsuarioMax.push_back(datoMin);
                }
        
        }

    }
cout<<endl;
    //VER DATOS USUARIO DEBUG
    
    //for(int a=0; a<datosUsuarioMax.size(); a++ ){

    //    cout<<datosUsuarioMax[a]<<" ";
    //}
    //cout<<endl;
    //for(int b=0; b<datosUsuarioMin.size(); b++){

    //    cout<<datosUsuarioMin[b]<<" ";
    //} 
    cout<<endl;

    cout<<"RESULTADOS: \n"<<endl;

    //IMPRIME LOS TITULOS 
    for(int k=0; k<titulo.size(); k++){

        cout<<titulo[k].substr(0,6)<<"\t";
        if(k == 0){ //para cuadrar los titulos con los resultados
            cout<<"\t";
        }
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
                    
                    cout<<matriz[u][0]<<"\t";

                    if( datosUsuarioMin[n-1] == matriz[u][n] ){
                        
                        cout<<"\tO";
                    } 
                    else{
                        cout<<"\tX";
                    }
                
                }else{ //si ya paso la parte de textura, hay que cambiar los string a double con la libreria sstring y la funcion stringstream
                     
                     double min, mid, max;

                    stringstream(datosUsuarioMin[n-1])>>min;
                    stringstream(matriz[u][n])>>mid;
                    stringstream(datosUsuarioMax[n-1])>>max;

                    if( (min - mid) <= 0 && (max - mid) >= 0 ){
                        
                        cout<<"\tO";
                    } 
                    else{
                        cout<<"\tX";
                    }

                }
              
            }

            cout<<endl;
        
    }

    return 0;

}
