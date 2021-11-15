#include "pagina.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <FS.h>
#include "SPIFFS.h"

#define file_ssid "/ssid.txt"
#define file_pass "/pass.txt"
#define btn_reset 23
#define led 2
bool estado_led;

//VIVOFIBRA-9501
//rgw7ucm3GT

const char *ssid = "ESP32";
const char *password = "";

String nome_rede, senha_rede;

String lista;



bool SETUP = true,INICIO = true;

AsyncWebServer server(80);
//=============================================================================//
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}//end void notFound()
//=============================================================================//
void setup(){
  Serial.begin(115200);
  pinMode(btn_reset,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
  delay(500);
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Scaneando Redes");
  int n = WiFi.scanNetworks();

  Serial.println("Completo");
  if (n == 0) {
      Serial.println("Sem redes encontradas");
  } else {
      String lista_redes[n];
      Serial.print(n);
      Serial.println(" Redes encontradas");
      for (int i = 0; i < n; ++i) {
        //Serial.print(i + 1);
        //Serial.print(": ");
        //Serial.print(WiFi.SSID(i));
        //Serial.print(" (");
        //Serial.print(WiFi.RSSI(i));
        //Serial.print(")");
        //Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        lista_redes[i] = WiFi.SSID(i);
        delay(100);
      }//end for n scan
    delay(500);
    for(int i = 0;i < n; i++){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      Serial.println(lista_redes[i]);
      lista += lista_redes[i] + "<br>";
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
      delay(100);
    } //end for n print     
  }//end if redes = 0

  Serial.println("Fim Scan\n");
  delay(500);
  openFS();
  while(INICIO){
    if(SETUP){
      WiFi.softAP(ssid, password);
      Serial.println();
      Serial.print("IP address: ");
      Serial.println(WiFi.softAPIP());
      SETUP = false;
      delay(500);
    }//end while SETUP
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html",

         "<!DOCTYPE html>\
          <html>\
          <head>\
            <meta charset='utf-8'>\
            <meta name='viewport' content='width=device-width, initial-scale=1'>\
            <title>Teste</title>\
          </head>\
          <body>\
          <span id='entrada'>"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
            + lista +
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        "</span>\
          <hr>\
          <span id='saida'></span>\
          <script>\
            sessionStorage.clear();\
            let dados = document.getElementById('entrada').innerHTML;\
            dados = dados.split('<br>');\
            console.log(dados);\
            let cont = 0;\
            dados.forEach(d =>{\
              cont++;\
              sessionStorage.setItem(cont, d);\
              sessionStorage.setItem('cont', cont - 1);\
            });\
            location.href = '/login';\
          </script>\
          </body>\
        </html>"
        );//webpageCore);
    }); 

    server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", webpageDados);
    });
  /*
    server.on("/dados", HTTP_GET, [] (AsyncWebServerRequest *request) {
      if (request->hasParam("ssid")) {
          nome_rede = request->getParam("ssid")->value();
      } else {
          nome_rede = "Sem dados";
      }
      if (request->hasParam("pass")) {
          senha_rede = request->getParam("pass")->value();
      } else {
          senha_rede = "Sem dados";
      }
      //request->send(200, "text/plain", "GET\n Nome: " + nome_rede + "\n Senha: " + senha_rede);
      request->send(200, "text/html", core);
      Serial.println(nome_rede);
      Serial.println(senha_rede);
      INICIO = false;
    });//end server on
  */
    server.on("/dados", HTTP_POST, [](AsyncWebServerRequest *request){
      if (request->hasParam("ssid", true)) {
          nome_rede = request->getParam("ssid", true)->value();
      } else {nome_rede = "Sem dados";}
      if (request->hasParam("ssid", true)) {
          senha_rede = request->getParam("pass", true)->value();
      } else {senha_rede = "Sem dados";}
      request->send(200, "text/html", webpageFinal);//"POST\n Nome: " + nome_rede + "\n Senha: " + senha_rede);
      
        Serial.print("Dados inseridos: ");
        Serial.print(nome_rede);
        Serial.print(" - ");
        Serial.print(senha_rede);
        Serial.println();
        //gravar dados SPIFFS
        INICIO = false;//sai do while inicio para testar os dados
    });//end server on
    server.onNotFound(notFound);
    server.begin();
    delay(100);
    estado_led = !estado_led;
    digitalWrite(led, estado_led);
  }//end while SETUP

  Serial.println("Fim setup inicio");

  char nome[50];//converte string para char
  nome_rede.toCharArray(nome, 50);
  Serial.println(nome);
  char senha[50];//converte string para char
  senha_rede.toCharArray(senha, 50);
  Serial.println(senha);

  WiFi.mode(WIFI_STA);
  WiFi.begin(nome, senha);
  int cont = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      reset();
      cont ++;
      Serial.print("Tentativa: ");
      Serial.println(cont);
      if(cont == 15){//se passar 15 segundos sem conectar volta ao inicio
        INICIO = true;
        Serial.println("Reiniciando");
        ESP.restart();
      }//end if cont
  }//end while wifi status
  Serial.println("\nCONNECTED"); //se conectado na rede salva os dados
  writeFile(nome_rede,file_ssid);
  writeFile(senha_rede,file_pass);
}//end setup()
//=============================================================================//
void loop(){
  reset();//le o botao por 5 segundos para zerar a memoria
  Serial.println(WiFi.localIP());
  delay(5000);
  estado_led = !estado_led;
  digitalWrite(led, estado_led);
}//end loop()
//=============================================================================//
void openFS(void) {
  if (!SPIFFS.begin()) {
    Serial.println("\n SPIFFS Erro ao abrir n");
  } else {
    nome_rede = readFile(file_ssid);
    Serial.print("Rede: ");
    Serial.println(nome_rede);

    senha_rede = readFile(file_pass);
    Serial.print("Pass: ");
    Serial.println(senha_rede);
  }
  if (nome_rede == "" or senha_rede == "") {
    Serial.println("Sem dados salvos");//CHAMAR TELA DE ENTRADA DE DADOS DA REDE
    INICIO = true;//cria servidor web
  } else {
    Serial.println("Ok");
    INICIO = false;//pula servidor web
  }//end teste de dados
  delay(500);
}//end open FS
String readFile(String path) {
  File rFile = SPIFFS.open(path, "r");
  if (!rFile) {
    Serial.println("Erro ao ler o arquivo");
  }
  String content = rFile.readStringUntil('\r'); //desconsidera '\r\n'
  rFile.close();
  return content;
}//end read file
//=============================================================================//
void writeFile(String state, String path) {
  File rFile = SPIFFS.open(path, "w+");
  if (!rFile) {
    Serial.println("Erro ao abrir arquivo!");
  } else {
    rFile.println(state);
    Serial.println("Arquivo criado");
  }
  rFile.close();
}//end write file
//=============================================================================//
void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}//end delete files
//=============================================================================//
void reset(){
  int cont = 0;
  while(!digitalRead(btn_reset)){//le o botao por 5 segundos para zerar a memoria
    cont++;
    Serial.print("Reset: ");
    Serial.println(cont);
    if(cont >= 5){
      deleteFile(SPIFFS, file_ssid);//deleta arquivo de rede
      deleteFile(SPIFFS, file_pass);//deleta arquivo de rede
      Serial.println("Reiniciando");
      delay(500);
      ESP.restart();
    }
    delay(1000);
  }//end while btn_reset
  while(WiFi.status() != WL_CONNECTED){
    cont++;
    Serial.print("Reconectando: ");
    Serial.println(cont);
    if(cont >= 10){
      Serial.println("Reiniciando: ");
      delay(500);
      ESP.restart();
    }
    delay(1000); 
  }//end while wifi status  
}//end reset()
//=============================================================================//
