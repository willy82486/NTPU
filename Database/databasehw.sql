-- phpMyAdmin SQL Dump
-- version 5.3.0-dev+20220511.c3fb567b13
-- https://www.phpmyadmin.net/
--
-- 主機： localhost
-- 產生時間： 2022-05-14 16:28:07
-- 伺服器版本： 10.4.24-MariaDB
-- PHP 版本： 8.1.5
create database `databasehw`;
use `databasehw`;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `databasehw`
--

-- --------------------------------------------------------

--
-- 資料表結構 `batting performance`
--

CREATE TABLE `batting performance` (
  `PlayerID` int(8) NOT NULL,
  `BattingID` int(11) NOT NULL,
  `Season` int(11) NOT NULL,
  `GameNumber` int(11) NOT NULL,
  `AB` int(2) NOT NULL DEFAULT 0,
  `Hit` int(2) NOT NULL DEFAULT 0,
  `HomeRun` int(2) NOT NULL DEFAULT 0,
  `RBI` int(2) NOT NULL DEFAULT 0,
  `R` int(2) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `batting performance`
--

INSERT INTO `batting performance` (`PlayerID`, `BattingID`, `Season`, `GameNumber`, `AB`, `Hit`, `HomeRun`, `RBI`, `R`) VALUES
(1, 1, 31, 1, 4, 3, 0, 1, 2),
(1, 2, 31, 3, 5, 4, 1, 3, 2),
(1, 3, 31, 5, 5, 4, 0, 1, 3),
(1, 4, 31, 9, 5, 2, 0, 1, 1),
(1, 5, 32, 1, 5, 5, 0, 2, 4),
(1, 6, 32, 3, 5, 1, 0, 3, 1),
(1, 7, 32, 9, 4, 3, 1, 1, 1),
(3, 1, 31, 1, 4, 0, 0, 0, 0),
(3, 2, 31, 3, 5, 1, 0, 0, 0),
(3, 3, 31, 7, 5, 2, 0, 0, 1),
(3, 4, 31, 8, 5, 3, 0, 3, 2),
(7, 1, 31, 2, 4, 2, 2, 3, 2),
(7, 2, 31, 4, 4, 1, 0, 0, 0),
(11, 1, 31, 6, 4, 1, 0, 0, 1),
(11, 2, 31, 9, 5, 2, 0, 0, 1);

-- --------------------------------------------------------

--
-- 資料表結構 `game`
--

CREATE TABLE `game` (
  `Season` int(11) NOT NULL,
  `GameNumber` int(11) NOT NULL,
  `GameDate` date NOT NULL,
  `Place` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Crowd` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `game`
--

INSERT INTO `game` (`Season`, `GameNumber`, `GameDate`, `Place`, `Crowd`) VALUES
(31, 1, '2021-03-01', '台南棒球場', 3000),
(31, 2, '2021-03-01', '天母棒球場', 5000),
(31, 3, '2021-03-02', '台南棒球場', 5000),
(31, 4, '2021-03-02', '天母棒球場', 4000),
(31, 5, '2021-03-04', '新莊棒球場', 4000),
(31, 6, '2021-03-05', '桃園棒球場', 7000),
(31, 7, '2021-03-06', '台中洲際棒球場', 10000),
(31, 8, '2021-03-07', '台中洲際棒球場', 10000),
(31, 9, '2021-03-07', '桃園棒球場', 8800),
(31, 10, '2021-03-08', '台中洲際棒球場', 15000),
(31, 11, '2021-03-08', '桃園棒球場', 9400),
(32, 1, '2022-03-01', '台南棒球場', 5000),
(32, 2, '2021-03-01', '天母棒球場', 4000),
(32, 3, '2022-03-02', '台南棒球場', 5000),
(32, 4, '2022-03-02', '天母棒球場', 7000),
(32, 5, '2022-03-04', '新莊棒球場', 4000),
(32, 6, '2022-03-05', '桃園棒球場', 7000),
(32, 7, '2022-03-06', '台中洲際棒球場', 10000),
(32, 8, '2022-03-07', '台中洲際棒球場', 10000),
(32, 9, '2022-03-07', '桃園棒球場', 8800),
(32, 10, '2022-03-08', '台中洲際棒球場', 15000),
(32, 11, '2022-03-08', '桃園棒球場', 9400);

-- --------------------------------------------------------

--
-- 資料表結構 `pitching performance`
--

CREATE TABLE `pitching performance` (
  `PlayerID` int(8) NOT NULL,
  `PitchingID` int(11) NOT NULL,
  `Season` int(11) NOT NULL,
  `GameNumber` int(11) NOT NULL,
  `IP` decimal(3,1) NOT NULL DEFAULT 0.0,
  `R` int(2) NOT NULL DEFAULT 0,
  `ER` int(2) NOT NULL DEFAULT 0,
  `IRA` int(2) NOT NULL DEFAULT 0,
  `WorL` varchar(1) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `SVorHorBS` varchar(2) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `pitching performance`
--

INSERT INTO `pitching performance` (`PlayerID`, `PitchingID`, `Season`, `GameNumber`, `IP`, `R`, `ER`, `IRA`, `WorL`, `SVorHorBS`) VALUES
(1, 1, 31, 1, '1.0', 0, 0, 0, NULL, NULL),
(2, 1, 31, 1, '7.1', 0, 0, 0, 'W', NULL),
(2, 2, 31, 9, '6.0', 1, 1, 0, 'W', NULL),
(2, 3, 32, 1, '8.0', 0, 0, 0, 'W', NULL),
(4, 1, 31, 7, '1.0', 0, 0, 0, NULL, 'SV'),
(4, 2, 32, 7, '1.0', 0, 0, 0, NULL, 'SV'),
(6, 1, 31, 2, '8.0', 0, 0, 0, 'W', NULL),
(6, 2, 32, 2, '5.1', 5, 5, 0, 'L', NULL),
(8, 1, 31, 5, '5.0', 5, 1, 4, 'L', NULL),
(8, 2, 32, 6, '7.0', 1, 1, 0, 'W', NULL),
(10, 1, 31, 6, '5.1', 2, 2, 0, NULL, NULL),
(10, 2, 32, 5, '7.0', 4, 1, 3, 'W', NULL);

-- --------------------------------------------------------

--
-- 資料表結構 `play`
--

CREATE TABLE `play` (
  `HomeTeam` varchar(5) COLLATE utf8mb4_unicode_ci NOT NULL,
  `AwayTeam` varchar(5) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Season` int(11) NOT NULL,
  `GameNumber` int(11) NOT NULL,
  `Score` int(2) NOT NULL,
  `R` int(2) NOT NULL,
  `W/L` varchar(1) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `play`
--

INSERT INTO `play` (`HomeTeam`, `AwayTeam`, `Season`, `GameNumber`, `Score`, `R`, `W/L`) VALUES
('中信兄弟', '味全龍', 31, 7, 1, 0, 'W'),
('中信兄弟', '味全龍', 31, 8, 7, 9, 'L'),
('中信兄弟', '味全龍', 32, 7, 5, 4, 'W'),
('中信兄弟', '味全龍', 32, 8, 5, 4, 'W'),
('中信兄弟', '富邦悍將', 31, 10, 5, 4, 'W'),
('中信兄弟', '富邦悍將', 32, 10, 5, 13, 'L'),
('味全龍', '富邦悍將', 31, 2, 8, 0, 'W'),
('味全龍', '富邦悍將', 31, 4, 7, 6, 'W'),
('味全龍', '富邦悍將', 32, 4, 1, 0, 'W'),
('味全龍', '樂天桃猿', 32, 2, 8, 9, 'L'),
('富邦悍將', '樂天桃猿', 32, 5, 7, 9, 'L'),
('富邦悍將', '統一獅', 31, 5, 8, 9, 'L'),
('樂天桃猿', '味全龍', 31, 6, 4, 6, 'L'),
('樂天桃猿', '味全龍', 31, 11, 5, 4, 'W'),
('樂天桃猿', '味全龍', 32, 11, 4, 9, 'L'),
('樂天桃猿', '富邦悍將', 32, 6, 4, 10, 'L'),
('樂天桃猿', '統一獅', 31, 9, 4, 10, 'L'),
('樂天桃猿', '統一獅', 32, 9, 3, 10, 'L'),
('統一獅', '中信兄弟', 31, 1, 9, 3, 'W'),
('統一獅', '中信兄弟', 31, 3, 7, 3, 'W'),
('統一獅', '中信兄弟', 32, 1, 9, 1, 'W'),
('統一獅', '中信兄弟', 32, 3, 6, 4, 'W');

-- --------------------------------------------------------

--
-- 資料表結構 `player`
--

CREATE TABLE `player` (
  `PlayerID` int(8) NOT NULL,
  `Sex` varchar(1) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Birthday` date NOT NULL,
  `PlayerName` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Left or Right` varchar(2) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Height` int(3) NOT NULL,
  `Weight` int(3) NOT NULL,
  `Nation` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `TeamName` varchar(5) COLLATE utf8mb4_unicode_ci NOT NULL,
  `JoinDate` date NOT NULL,
  `LeaveDate` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `player`
--

INSERT INTO `player` (`PlayerID`, `Sex`, `Birthday`, `PlayerName`, `Left or Right`, `Height`, `Weight`, `Nation`, `TeamName`, `JoinDate`, `LeaveDate`) VALUES
(1, 'M', '1994-01-07', '陳傑憲', 'RL', 173, 73, '台灣', '統一獅', '2016-07-29', NULL),
(2, 'M', '1982-03-05', '潘威倫', 'RR', 182, 98, '台灣', '統一獅', '2003-03-09', NULL),
(3, 'M', '1991-07-03', '王威晨', 'RL', 183, 75, '台灣', '中信兄弟', '2016-04-26', NULL),
(4, 'M', '1991-07-03', '李振昌', 'RR', 180, 87, '台灣', '中信兄弟', '2018-07-25', NULL),
(5, 'M', '1972-05-28', 'Tilson Brito', 'RR', 183, 90, '多明尼加', '統一獅', '2006-08-17', '2009-07-01'),
(6, 'M', '1992-04-25', '王維中', 'LL', 188, 83, '台灣', '味全龍', '2021-03-14', NULL),
(7, 'M', '1982-01-01', '林智勝', 'RR', 183, 108, '台灣', '味全龍', '2021-10-31', NULL),
(8, 'M', '1993-11-10', '江少慶', 'RR', 183, 94, '台灣', '富邦悍將', '2021-08-25', NULL),
(9, 'M', '1985-11-11', '林益全', 'RL', 183, 83, '台灣', '富邦悍將', '2009-03-29', NULL),
(10, 'M', '1990-10-29', '陳冠宇', 'LL', 178, 80, '台灣', '樂天桃猿', '2021-08-24', NULL),
(11, 'M', '1997-12-12', '陳晨威', 'RL', 180, 72, '台灣', '樂天桃猿', '2018-10-09', NULL);

-- --------------------------------------------------------

--
-- 資料表結構 `player's school`
--

CREATE TABLE `player's school` (
  `Player_ID` int(8) NOT NULL,
  `School` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `player's school`
--

INSERT INTO `player's school` (`Player_ID`, `School`) VALUES
(1, '大仁國中'),
(1, '文化大學'),
(1, '高雄市三民高中'),
(1, '高雄市中正國小'),
(2, '九州別府大學'),
(2, '美和中學'),
(2, '赤山國小'),
(2, '輔仁大學'),
(3, '福林國小'),
(3, '穀保家商'),
(3, '輔仁大學'),
(3, '重慶國中'),
(4, '台北體院'),
(4, '屏東高中'),
(4, '馬公國中'),
(4, '龍門國小'),
(6, '臺灣體大'),
(7, '善化國中'),
(7, '善化國小'),
(7, '善化高中'),
(8, '文化大學'),
(8, '穀保家商'),
(9, '南英商工'),
(10, '國立體育大學'),
(10, '穀保家商'),
(11, '大同技術學院'),
(11, '屏東中學');

-- --------------------------------------------------------

--
-- 資料表結構 `team`
--

CREATE TABLE `team` (
  `TeamName` varchar(5) COLLATE utf8mb4_unicode_ci NOT NULL,
  `TeamBirthday` date NOT NULL,
  `TeamHomeCourt` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- 傾印資料表的資料 `team`
--

INSERT INTO `team` (`TeamName`, `TeamBirthday`, `TeamHomeCourt`) VALUES
('中信兄弟', '2014-01-01', '台中洲際棒球場'),
('味全龍', '2019-11-30', '天母棒球場'),
('富邦悍將', '2017-01-01', '新莊棒球場'),
('樂天桃猿', '2019-06-30', '桃猿棒球場'),
('統一獅', '1990-01-01', '台南棒球場');

--
-- 已傾印資料表的索引
--

--
-- 資料表索引 `batting performance`
--
ALTER TABLE `batting performance`
  ADD PRIMARY KEY (`PlayerID`,`BattingID`) USING BTREE,
  ADD KEY `PlayGame` (`Season`,`GameNumber`);

--
-- 資料表索引 `game`
--
ALTER TABLE `game`
  ADD PRIMARY KEY (`Season`,`GameNumber`);

--
-- 資料表索引 `pitching performance`
--
ALTER TABLE `pitching performance`
  ADD PRIMARY KEY (`PlayerID`,`PitchingID`) USING BTREE,
  ADD KEY `PitchGame` (`Season`,`GameNumber`);

--
-- 資料表索引 `play`
--
ALTER TABLE `play`
  ADD PRIMARY KEY (`HomeTeam`,`AwayTeam`,`Season`,`GameNumber`),
  ADD KEY `AwayTeamName` (`AwayTeam`),
  ADD KEY `Match` (`Season`,`GameNumber`);

--
-- 資料表索引 `player`
--
ALTER TABLE `player`
  ADD PRIMARY KEY (`PlayerID`),
  ADD KEY `Belong to` (`TeamName`);

--
-- 資料表索引 `player's school`
--
ALTER TABLE `player's school`
  ADD PRIMARY KEY (`Player_ID`,`School`);

--
-- 資料表索引 `team`
--
ALTER TABLE `team`
  ADD PRIMARY KEY (`TeamName`);

--
-- 在傾印的資料表使用自動遞增(AUTO_INCREMENT)
--

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `batting performance`
--
ALTER TABLE `batting performance`
  MODIFY `PlayerID` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- 使用資料表自動遞增(AUTO_INCREMENT) `pitching performance`
--
ALTER TABLE `pitching performance`
  MODIFY `PlayerID` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- 已傾印資料表的限制式
--

--
-- 資料表的限制式 `batting performance`
--
ALTER TABLE `batting performance`
  ADD CONSTRAINT `PlayGame` FOREIGN KEY (`Season`,`GameNumber`) REFERENCES `game` (`Season`, `GameNumber`),
  ADD CONSTRAINT `PlayPlayer` FOREIGN KEY (`PlayerID`) REFERENCES `player` (`PlayerID`);

--
-- 資料表的限制式 `pitching performance`
--
ALTER TABLE `pitching performance`
  ADD CONSTRAINT `PitchGame` FOREIGN KEY (`Season`,`GameNumber`) REFERENCES `game` (`Season`, `GameNumber`),
  ADD CONSTRAINT `Pitcher` FOREIGN KEY (`PlayerID`) REFERENCES `player` (`PlayerID`);

--
-- 資料表的限制式 `play`
--
ALTER TABLE `play`
  ADD CONSTRAINT `AwayTeamName` FOREIGN KEY (`AwayTeam`) REFERENCES `team` (`TeamName`),
  ADD CONSTRAINT `HomeTeamName` FOREIGN KEY (`HomeTeam`) REFERENCES `team` (`TeamName`),
  ADD CONSTRAINT `Match` FOREIGN KEY (`Season`,`GameNumber`) REFERENCES `game` (`Season`, `GameNumber`);

--
-- 資料表的限制式 `player`
--
ALTER TABLE `player`
  ADD CONSTRAINT `Belong to` FOREIGN KEY (`TeamName`) REFERENCES `team` (`TeamName`);

--
-- 資料表的限制式 `player's school`
--
ALTER TABLE `player's school`
  ADD CONSTRAINT `Player` FOREIGN KEY (`Player_ID`) REFERENCES `player` (`PlayerID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;



