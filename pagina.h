const char webpageDados[] =
R"=====(
<!DOCTYPE html>
  <html>
  <!------------------------------C S S--------------------------------->
    <head>
      <style>
        a{
          text-decoration: none;
          }
        table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
        width: 70%;
      }
      </style>
    </head>
  <!----------------------------H T M L--------------------------------->
    <body>
      <div align="center">
        <form action="/dados" method="POST"><h1>Dados da Rede</h1>
          <br><br>
            <label for="ssid">Rede:</label>
            <input type="text" name="ssid" placeholder="Nome da Rede">
          <br><br>
            <label for="pass">Senha:</label>
            <input type="text" name="pass" placeholder="Senha da Rede">
          <br><br>
            <button type="submit" name="end">Salvar</button>
        </form>
          <hr>

          <table>
            <tr>
              <th>Redes:</th>    
            </tr>
            <tr>
              <td><a>Rede Teste 1</a></td>
            </tr>
            <tr>
              <td><a>Rede Teste 2</a></td>
            </tr>
            <tr>
              <td><a>Rede Teste 3</a></td>
            </tr>
          </table>
      </div>
    <!---------------------------JavaScript------------------------------->
      <script>
         console.log("web Page Dados")
      </script>
    </body>
  </html>
)=====";

const char core[] =
R"=====(
<!DOCTYPE html>
  <html>
  <!------------------------------C S S--------------------------------->
    <head>

    </head>
  <!----------------------------H T M L--------------------------------->
    <body>

    <!---------------------------JavaScript------------------------------->
      <script>
         console.log("web Page core")
         //location.href = "/"
      </script>
    </body>
  </html>
)=====";

const char php[] =
R"=====(
<?php
  echo "OK";
?>
)=====";
