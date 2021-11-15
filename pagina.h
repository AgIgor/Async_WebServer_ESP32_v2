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

          <button type="submit">Salvar</button>
        </form>
      </div>
    <!---------------------------JavaScript------------------------------->
      <script>
         console.log("web Page Dados")
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
    </head>
  <!----------------------------H T M L--------------------------------->
    <body>
    <!---------------------------JavaScript------------------------------->
      <script>
        alert("Tentando Conectar!");
        //location.reload();
        location.href = "/";
      </script>
    </body>
  </html>
)=====";