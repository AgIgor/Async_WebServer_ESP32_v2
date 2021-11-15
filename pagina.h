const char webpageDados[] =
R"=====(
<!DOCTYPE html>
  <html>
  <!------------------------------C S S--------------------------------->
    <head>
      <meta charset="utf-8">
      <title>Wifi Manager</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        html {
          font-family: Arial, Helvetica, sans-serif;
        }

        h1 {
          font-size: 1.8rem;
          color: white;
        }

        p{
          font-size: 20px;
          text-align: center;
        }

        .topnav {
          overflow: hidden;
          background-color: #0A1128;
          text-align: center;
        }

        body {
          margin: 0;
        }

        .content {
          padding: 20px;
          max-width: max-content;
          margin: 0 auto;
        }

        input[type=text], select {
          width: 100%;
          padding: 12px 20px;
          margin: 8px 0;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
        }

        form{
          border-radius: 5px;
          background-color: #f2f2f2;
          padding: 20px;
        }

        button {
          background-color: #034078;
          border: none;
          padding: 14px 20px;
          text-align: center;
          font-size: 20px;
          border-radius: 4px;
          transition-duration: 0.4s;
          width: 100%;
          color: white;
          cursor: pointer;
        }

        button:hover {
            background-color: #1282A2;
        }
        table{
          margin-top: 10%;
          border-radius: 4px;
          width: 100%;
        }
        table h1{
          color: black;
        }

      </style>
    </head>
  <!----------------------------H T M L--------------------------------->
    <body>
      <div class="topnav">
        <h1>Seleção de Rede <i class="fas fa-cogs"></i></h1>
      </div>
      <div class="content">
        <form action="/dados" method="POST">
          <label for="ssid">Nome</label>
          <input type="text" id="ssid" name="ssid">

          <label for="pass">Senha</label>
          <input type="text" id="pass" name="pass">

          <button type="submit" onclick="btn_salvar()">Salvar</button>
        </form>
        <table>
          <thead>
            <tr>
              <th><h1>Redes Disponiveis</h1><hr></th>
            </tr>
          </thead>
          <tbody id="tabelaLista">
          </tbody>
        </table>        
      </div>
    <!---------------------------JavaScript------------------------------->
      <script>  
        let ssid = [];

        let cont = sessionStorage.getItem('cont');
        console.log(cont);

        for(i = 0; i < cont; i++){
          ssid.push(sessionStorage.getItem(i));
        }

        console.log("Array",Array.isArray(ssid),ssid)
        ssid.forEach(i =>{

          let btn = document.createElement("button")
            btn.id = i
            btn.innerText = i
            btn.onclick = function(){
              clickSelect(this.id)
            }

          let tabela = document.getElementById("tabelaLista")
          var linha = tabela.insertRow()
                linha.insertCell(0).append(btn)
        })

        function clickSelect(id){
          console.log(id)
          document.getElementById("ssid").value = id; //define o compo de nome da rede
        }
        function btn_salvar(){
          sessionStorage.clear();//limpa dados armazenados
        }
      </script>
    </body>
  </html>
)=====";


const char webpageFinal[] =
R"=====(
<!DOCTYPE html>
  <html>
  <!------------------------------C S S--------------------------------->
    <head>
      <meta charset="utf-8">
      <title>Wifi Manager</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        html {
          font-family: Arial, Helvetica, sans-serif;
        }

        h1 {
          font-size: 1.8rem;
          color: white;
        }

        p{
          font-size: 20px;
          text-align: center;
        }

        .topnav {
          overflow: hidden;
          background-color: #0A1128;
          text-align: center;
        }

        body {
          margin: 0;
        }

        .content {
          padding: 20px;
          max-width: max-content;
          margin: 0 auto;
        }

        input[type=text], select {
          width: 100%;
          padding: 12px 20px;
          margin: 8px 0;
          display: inline-block;
          border: 1px solid #ccc;
          border-radius: 4px;
          box-sizing: border-box;
        }

        form{
          border-radius: 5px;
          background-color: #f2f2f2;
          padding: 20px;
        }

        button {
          background-color: #034078;
          border: none;
          padding: 14px 20px;
          text-align: center;
          font-size: 20px;
          border-radius: 4px;
          transition-duration: 0.4s;
          width: 100%;
          color: white;
          cursor: pointer;
        }

        button:hover {
            background-color: #1282A2;
        }
        table{
          margin-top: 10%;
          border-radius: 4px;
          width: 100%;
        }
        table h1{
          color: black;
        }

      </style>
    </head>
  <!----------------------------H T M L--------------------------------->
    <body>
    <!---------------------------JavaScript------------------------------->
      <div class="topnav">
          <h1>Seleção de Rede <i class="fas fa-cogs"></i></h1>
        </div>
      <div class="content">       
        <button onclick="btn_voltar()">Voltar</button>
        <h2 id="saida"></h2>
      </div>
      <script>

        document.getElementById("saida")innerHTML = "Conectando em: <br>" + sessionStorage.getItem('ssid') +"<br>"+ sessionStorage.getItem('pass')

        function btn_voltar(){
          sessionStorage.clear();
          window.history.back();
        }
        //location.reload()
        //location.href = "teste.html"
      </script>
        </body>
  </html>
)=====";

/*
const char webpageCore[] =
R"=====(
<!DOCTYPE html>
  <html>
  <!------------------------------C S S--------------------------------->
    <head>
      <meta charset="utf-8">
      <title>Wifi Manager</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
    </head>
  <!----------------------------H T M L--------------------------------->
    <body>
    <!---------------------------JavaScript------------------------------->
      <script>
        //location.href = "/index"
      </script>
        </body>
  </html>
)=====";
*/