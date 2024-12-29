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
        <title>CPBL各球員網站</title>
</head>
<h1> CPBL球員資訊 </h1>
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
$ID = $_GET['id'];
//-----------------------------------------------------------------------------------------------------------------------------------打者

$sql = "SELECT PlayerName, player.TeamName AS 'TEAMNAME', game.Season AS 'SEASON', game.GameNumber AS 'GAMENUMBER', HomeTeam, AwayTeam, AB, Hit, HomeRun, RBI, `batting performance`.R AS 'SCORE'
        FROM `player`,`game`,`batting performance`,`play`,`team`
        WHERE PlayerName='$ID' AND `player`.PlayerID=`batting performance`.PlayerID AND
            `batting performance`.Season=`game`.Season AND `batting performance`.GameNumber=`game`.GameNumber AND
            `play`.Season=`game`.Season AND `play`.GameNumber=`game`.GameNumber AND
            `team`.TeamName=`player`.TeamName AND
            (HomeTeam=`player`.TeamName OR AwayTeam=`player`.TeamName)";      
// 用mysqli_query方法執行(sql語法)將結果存在變數中
$result_batting = mysqli_query($connect_DB, $sql);
?>
<div style="margin: 15px 20px 25px 500px; position:relative; bottom:10px; font-size:25px">
<h2 style="color:red">打擊成績</h2>
<?php
// 如果有資料
if ($result_batting) {
    // mysqli_num_rows方法可以回傳我們結果總共有幾筆資料
    if (mysqli_num_rows($result_batting)>0) {
        // 取得大於0代表有資料
        // while迴圈會根據資料數量，決定跑的次數
        // mysqli_fetch_assoc方法可取得一筆值
        while ($row = mysqli_fetch_array($result_batting, MYSQLI_NUM)) {
            // 每跑一次迴圈就抓一筆值，最後放進data陣列中
            $datas_batting[] = $row;
        }
    }
    // 釋放資料庫查到的記憶體
    mysqli_free_result($result_batting);
}
else {
    echo "{$sql} 語法執行失敗，錯誤訊息: " . mysqli_error($connect_DB);
}
?>
<?php
// 處理完後印出資料
if(!empty($result_batting)){
?>  <?php
    // 如果結果不為空，就利用print_r方法印出資料
    //print_r($datas);
    if(!isset($datas_batting)){
        $datas_batting = null;
    }
    ?>
    <?php
    if($datas_batting == null){
    ?>
        <h3 style="color:red">該名選手沒有打擊紀錄</h3>
    <?php
    }
    else{
    ?>
        <table border=3>
        <tr>
        <td>球員名稱</td>
        <td>效力球隊</td>
        <td>賽季</td>
        <td>比賽編號</td>
        <td>主場/客場</td>
        <td>敵方隊伍</td>
        <td>打數</td>
        <td>安打</td>
        <td>全壘打</td>
        <td>打點</td>
        <td>得分</td>
    </tr>
        <?php
        foreach($datas_batting as $key => $value){
        ?>
            <tr>
            <td><?php echo $value[0] ?></td>
            <td><?php echo $value[1] ?></td>
            <td><?php echo $value[2] ?></td>
            <td><?php echo $value[3] ?></td>
            <?php
            if($value[1] == $value[4]){
            ?>
                <td>主場</td>
            <?php
            }
            else{
            ?>
                <td>客場</td>
            <?php
            }
            if($value[1] == $value[4]){
            ?>
                <td><?php echo $value[5] ?></td>
            <?php
            }
            else{
            ?>
                <td><?php echo $value[4] ?></td>
            <?php
            }
            ?>
            <td><?php echo $value[6] ?></td>
            <td><?php echo $value[7] ?></td>
            <td><?php echo $value[8] ?></td>
            <td><?php echo $value[9] ?></td>
            <td><?php echo $value[10] ?></td>
            </tr>
        <?php
        }
        ?>
   <?php
    }
    ?>
    </table>
    <?php
    $sql = "SELECT COUNT(*)
    FROM `player`,`game`,`batting performance`,`play`,`team`
    WHERE PlayerName='$ID' AND `player`.PlayerID=`batting performance`.PlayerID AND
        `batting performance`.Season=`game`.Season AND `batting performance`.GameNumber=`game`.GameNumber AND
        `play`.Season=`game`.Season AND `play`.GameNumber=`game`.GameNumber AND
        `team`.TeamName=`player`.TeamName AND
        (HomeTeam=`player`.TeamName OR AwayTeam=`player`.TeamName)
    GROUP BY PlayerName"; 
    $result_batting_total = mysqli_query($connect_DB, $sql);
    if ($result_batting_total) {
        // mysqli_num_rows方法可以回傳我們結果總共有幾筆資料
        if (mysqli_num_rows($result_batting_total)>0) {
            // 取得大於0代表有資料
            // while迴圈會根據資料數量，決定跑的次數
            // mysqli_fetch_assoc方法可取得一筆值
            while ($row = mysqli_fetch_array($result_batting_total, MYSQLI_NUM)) {
                // 每跑一次迴圈就抓一筆值，最後放進data陣列中
                $datas_batting_total[] = $row;
            }
        }
        // 釋放資料庫查到的記憶體
        mysqli_free_result($result_batting_total);
    }
    if(!isset($datas_batting_total)){
        $datas_batting_total = null;
    }
    if($datas_batting_total != null){
        foreach($datas_batting_total as $key => $value)
            print '總出賽數 :'.$value[0];
    }
    ?>
<?php
}
?>


</div>

<?php
//-----------------------------------------------------------------------------------------------------------------------------------投手
$sql = "SELECT PlayerName, player.TeamName AS 'TEAMNAME', game.Season AS 'SEASON', game.GameNumber AS 'GAMENUMBER', HomeTeam, AwayTeam, IP, `pitching performance`.R AS '失分', ER, IRA, WorL, SVorHorBS
        FROM `player`,`game`,`pitching performance`,`play`,`team`
        WHERE PlayerName='$ID' AND `player`.PlayerID=`pitching performance`.PlayerID AND
            `pitching performance`.Season=`game`.Season AND `pitching performance`.GameNumber=`game`.GameNumber AND
            `play`.Season=`game`.Season AND `play`.GameNumber=`game`.GameNumber AND
            `team`.TeamName=`player`.TeamName AND
            (HomeTeam=`player`.TeamName OR AwayTeam=`player`.TeamName)";
// 用mysqli_query方法執行(sql語法)將結果存在變數中
$result_pitching = mysqli_query($connect_DB, $sql);
print'<div style="margin: 15px 20px 25px 500px; font-size:25px">';
print '<h2 style="color:red;">投球成績</h2>';
// 如果有資料
if ($result_pitching) {
    // mysqli_num_rows方法可以回傳我們結果總共有幾筆資料
    if (mysqli_num_rows($result_pitching)>0) {
        // 取得大於0代表有資料
        // while迴圈會根據資料數量，決定跑的次數
        // mysqli_fetch_assoc方法可取得一筆值
        while ($row = mysqli_fetch_array($result_pitching, MYSQLI_NUM)) {
            // 每跑一次迴圈就抓一筆值，最後放進data陣列中
            $datas_pitching[] = $row;
        }
    }
    // 釋放資料庫查到的記憶體
    mysqli_free_result($result_pitching);
}
else {
    echo "{$sql} 語法執行失敗，錯誤訊息: " . mysqli_error($connect_DB);
}
// 處理完後印出資料
if(!empty($result_pitching)){
    // 如果結果不為空，就利用print_r方法印出資料
    //print_r($datas);
    if(!isset($datas_pitching)){
        $datas_pitching = null;
    }
    if($datas_pitching == null){
        print '<h3 style="color:red">該名選手沒有投球紀錄</h3>';
    }
    else{
        print '<table border=3>';
        print '<tr>';
        print '<td>'."球員名稱".'</td>';
        print '<td>'."效力球隊".'</td>';
        print '<td>'."賽季".'</td>';
        print '<td>'."比賽編號".'</td>';
        print '<td>'."主場/客場".'</td>';
        print '<td>'."敵方隊伍".'</td>';
        print '<td>'."投球局數".'</td>';
        print '<td>'."失分".'</td>';
        print '<td>'."責失分".'</td>';
        print '<td>'."非責失分".'</td>';
        print '<td>'."W/L".'</td>';
        print '<td>'."SV/H/BS".'</td>';
        print '</tr>';
        foreach($datas_pitching as $key => $value){
            print '<tr>';
            print '<td>'.$value[0].'</td>';
            print '<td>'.$value[1].'</td>';
            print '<td>'.$value[2].'</td>';
            print '<td>'.$value[3].'</td>';
            if($value[1] == $value[4]){
                print '<td>'."主場".'</td>';
            }
            else{
                print '<td>'."客場".'</td>';
            }
            if($value[1] == $value[4]){
                print '<td>'.$value[5].'</td>';
            }
            else{
                print '<td>'.$value[4].'</td>';
            }
            print '<td>'.$value[6].'</td>';
            print '<td>'.$value[7].'</td>';
            print '<td>'.$value[8].'</td>';
            print '<td>'.$value[9].'</td>';
            if($value[10] == null){
                print '<td>'.'無'.'</td>';
            }
            else{
                print '<td>'.$value[10].'</td>';
            }
            if($value[11] == null){
                print '<td>'.'無'.'</td>';
            }
            else{
                print '<td>'.$value[11].'</td>';
            }
            print '</tr>';
        }
    }
    print '</table >';
    $sql = "SELECT COUNT(*)
        FROM `player`,`game`,`pitching performance`,`play`,`team`
        WHERE PlayerName='$ID' AND `player`.PlayerID=`pitching performance`.PlayerID AND
            `pitching performance`.Season=`game`.Season AND `pitching performance`.GameNumber=`game`.GameNumber AND
            `play`.Season=`game`.Season AND `play`.GameNumber=`game`.GameNumber AND
            `team`.TeamName=`player`.TeamName AND
            (HomeTeam=`player`.TeamName OR AwayTeam=`player`.TeamName)
        GROUP BY PlayerName";
    $result_pitching_total = mysqli_query($connect_DB, $sql);
    if ($result_pitching_total) {
        // mysqli_num_rows方法可以回傳我們結果總共有幾筆資料
        if (mysqli_num_rows($result_pitching_total)>0) {
            // 取得大於0代表有資料
            // while迴圈會根據資料數量，決定跑的次數
            // mysqli_fetch_assoc方法可取得一筆值
            while ($row = mysqli_fetch_array($result_pitching_total, MYSQLI_NUM)) {
                // 每跑一次迴圈就抓一筆值，最後放進data陣列中
                $datas_pitching_total[] = $row;
            }
        }
        // 釋放資料庫查到的記憶體
        mysqli_free_result($result_pitching_total);
    }
    if(!isset($datas_pitching_total)){
        $datas_pitching_total = null;
    }
    if($datas_pitching_total != null){
        foreach($datas_pitching_total as $key => $value)
            print '總出賽數 :'.$value[0];
    }
}
else {
    // 為空表示沒資料
    echo "查無資料";
}
print '</div>'
?>