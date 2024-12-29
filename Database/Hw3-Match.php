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
        <title>CPBL比賽網站</title>
    </head>
<h1> CPBL歷史賽程 </h1>
<hr/>
<body>
<div style = "background-color : #BEBEBE ; font-size:20px; ">
    <div class ="col">
    <h3>查詢</h3>
        <a href="Hw3-PlayerList.php"><button>球員資料</button></a>
        <a href="Hw3-Team.php"><button>球團資料</button></a>
        <a href="Hw3-Match.php"><button>比賽資訊</button></a>
        <a href="index.php"><button>主頁</button></a>
    </div>
</div>
</body>
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

$sql = "SELECT * FROM `play` ORDER BY Season,GameNumber";
// 用mysqli_query方法執行(sql語法)將結果存在變數中
$result = mysqli_query($connect_DB, $sql);
print'<div style="margin: 15px 20px 25px 450px; font-size:30px">';
print '<h2 style="color:red">'.'歷史對戰紀錄'.'</h2>';
// 如果有資料
if ($result) {
    // mysqli_num_rows方法可以回傳我們結果總共有幾筆資料
    if (mysqli_num_rows($result)>0) {
        // 取得大於0代表有資料
        // while迴圈會根據資料數量，決定跑的次數
        // mysqli_fetch_assoc方法可取得一筆值
        while ($row = mysqli_fetch_array($result, MYSQLI_NUM)) {
            // 每跑一次迴圈就抓一筆值，最後放進data陣列中
            $datas[] = $row;
        }
    }
    // 釋放資料庫查到的記憶體
    mysqli_free_result($result);
}
else {
    echo "{$sql} 語法執行失敗，錯誤訊息: " . mysqli_error($connect_DB);
}
// 處理完後印出資料
if(!empty($result)){
    // 如果結果不為空，就利用print_r方法印出資料
    //print_r($datas);
    print '<table border=3>';
    print '<tr>';
    print '<td>'."賽季".'</td>';
    print '<td>'."比賽編號".'</td>';
    print '<td>'."主場球隊".'</td>';
    print '<td>'."客場球隊".'</td>';
    print '<td>'."主場球隊得分".'</td>';
    print '<td>'."客場球隊得分".'</td>';
    print '<td>'."獲勝隊伍".'</td>';
    print '</tr>';
    foreach($datas as $key => $value){
        print '<tr>';
        print '<td>'.$value[2].'</td>';
        print '<td>'.$value[3].'</td>';
        print '<td>'.$value[0].'</td>';
        print '<td>'.$value[1].'</td>';
        print '<td>'.$value[4].'</td>';
        print '<td>'.$value[5].'</td>';
        if($value[4] > $value[5])
            print '<td>'.$value[0].'</td>';
        else
        print '<td>'.$value[1].'</td>';
        print '</tr>';
    }
    print'</table>';
}
else {
    // 為空表示沒資料
    echo "查無資料";
}
$Lionwin = 0;
$Lionlose = 0;
$Elephantwin = 0;
$Elephantlose = 0;
$Dragonwin = 0;
$Dragonlose = 0;
$Monkeywin = 0;
$Monkeylose = 0;
$Guardwin = 0;
$Guardlose = 0;
foreach($datas as $key => $value){
    if($value[0] == "統一獅"){
        if($value[6] == "W"){
            $Lionwin++;
        }
        else{
            $Lionlose++;
        }
    }
    else if($value[0] == "中信兄弟"){
        if($value[6] == "W"){
            $Elephantwin++;
        }
        else{
            $Elephantlose++;
        }
    }
    else if($value[0] == "味全龍"){
        if($value[6] == "W"){
            $Dragonwin++;
        }
        else{
            $Dragonlose++;
        }
    }
    else if($value[0] == "樂天桃猿"){
        if($value[6] == "W"){
            $Monkeywin++;
        }
        else{
            $Monkeylose++;
        }
    }
    else if($value[0] == "富邦悍將"){
        if($value[6] == "W"){
            $Guardwin++;
        }
        else{
            $Guardlose++;
        }
    }
    if($value[1] == "統一獅"){
        if($value[6] == "L"){
            $Lionwin++;
        }
        else{
            $Lionlose++;
        }
    }
    
    else if($value[1] == "中信兄弟"){
        if($value[6] == "L"){
            $Elephantwin++;
        }
        else{
            $Elephantlose++;
        }
    }
    else if($value[1] == "味全龍"){
        if($value[6] == "L"){
            $Dragonwin++;
        }
        else{
            $Dragonlose++;
        }
    }

    else if($value[1] == "樂天桃猿"){
        if($value[6] == "L"){
            $Monkeywin++;
        }
        else{
            $Monkeylose++;
        }
    }
    else if($value[1] == "富邦悍將"){
        if($value[6] == "L"){
            $Guardwin++;
        }
        else{
            $Guardlose++;
        }
    }
}
print '<h2 style="color:red">'.'累積戰績'.'</h2>';
print '<table border=3>';
    print '<tr>';
    print '<td>'."球隊名稱".'</td>';
    print '<td>'."累積勝場".'</td>';
    print '<td>'."累積敗場".'</td>';
    print '</tr>';
    print '<td>'.'統一獅'.'</td>';
    print '<td>'.$Lionwin.'</td>';
    print '<td>'.$Lionlose.'</td>';
    print '</tr>';
    print '<tr>';
    print '<td>'.'味全龍'.'</td>';
    print '<td>'.$Dragonwin.'</td>';
    print '<td>'.$Dragonlose.'</td>';
    print '</tr>';
    print '<tr>';
    print '<td>'.'中信兄弟'.'</td>';
    print '<td>'.$Elephantwin.'</td>';
    print '<td>'.$Elephantlose.'</td>';
    print '</tr>';
    print '<tr>';
    print '<td>'.'樂天桃猿'.'</td>';
    print '<td>'.$Monkeywin.'</td>';
    print '<td>'.$Monkeylose.'</td>';
    print '</tr>';
    print '<tr>';
    print '<td>'.'富邦悍將'.'</td>';
    print '<td>'.$Guardwin.'</td>';
    print '<td>'.$Guardlose.'</td>';
    print '</tr>';
    print '<tr>';
print'</table>';


print '</div>'
?>
<body>
    
</body>
