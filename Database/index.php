<!DOCTYPE html>
<html>
<head>
        <!--***** meta標籤 *****-->
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
        <meta charset="UTF-8"></meta> <!--也可以寫成 <meta charset="UTF-8"/>-->
        <meta name="description" content="CPBL資訊網站"/>
        <meta name="author" content="邱信瑋"/>
        <meta name="keyword" content="邱信瑋,CPBL,html"/>
        <!--***** 網頁的名稱 *****-->
        <title>CPBL資訊網站</title>
    </head>
<h1> CPBL資訊網站 </h1>
<hr/>
<?php
// Server_name, Userneme, Password, Database_name 
$connect_DB = mysqli_connect('localhost', 'willy', 'W5110willy', 'databasehw');
if(!$connect_DB){
    echo 'Unsuccessful Connection';
    echo '<br/>';
    exit();
}
$flag = mysqli_select_db($connect_DB, 'databasehw');
if(!$flag){
    echo 'Cannot use this DataBase';
    echo '<br/>';
    exit();
}
mysqli_query($connect_DB,"SET NAMES 'utf8'");

//require_once 'Hw3DB.php';
?>
<body>
    <div style = "background-color : #BEBEBE ; font-size:20px; ">
        <div class ="col">
        <h3>查詢</h3>
            <a href="Hw3-PlayerList.php"><button>球員資料</button></a>
            <a href="Hw3-Team.php"><button>球團資料</button></a>
            <a href="Hw3-Match.php"><button>比賽資訊</button></a>
        </div>
    </div>
    <br/>
    <br/>
    <br/>
    <br/>
    <br/>
    <div style="margin: 50px 20px 25px 580px">
    <img src="CPBL.jpg" width="738" height="272"/>
    </div>
</body>
