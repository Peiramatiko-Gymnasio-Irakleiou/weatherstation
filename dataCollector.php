﻿<?php

/*
  ESP8266: send data  Domain


  Uses POST command to send DHT data to a designated website
  The circuit:
  * DHT
  * Post to Domain
*/


date_default_timezone_set("Europe/Athens");
$TimeStamp = "The current time  in Heraklion is  Η ώρα στο Ηράκλειο Κρήτης είναι : ".date("h:i:sa").date("  d/m/Y");
file_put_contents('dataDisplayer.html', $TimeStamp, FILE_APPEND);

   if( $_REQUEST["Humidity"] ||  $_REQUEST["Temperature_Cel"] ||
                      $_REQUEST["Temperature_Fehr"]
       ||  $_REQUEST["HeatIndex_Cel"] ||  $_REQUEST["HeatIndex_Fehr"] ) 
   {
   echo " The Humidity is: ". $_REQUEST['Humidity']. "%<br />";
   echo " The Temperature is: ". $_REQUEST['Temperature_Cel']. " Celcius<br />";
   echo " The Temperature is: ". $_REQUEST['Temperature_Fehr']. " Fehr<br />";
   echo " The Heat Index: ". $_REQUEST['HeatIndex_Cel']. " Heat Idx Cel<br />";
   echo " The Heat Index: ". $_REQUEST['HeatIndex_Fehr']. " Heat Idx Fehr<br />";
   }
	  
	
$var1 = $_REQUEST['Humidity'];
$var2 = $_REQUEST['Temperature_Cel'];
$var3 = $_REQUEST['Temperature_Fehr'];
$var4 = $_REQUEST['HeatIndex_Cel'];
$var5 = $_REQUEST['HeatIndex_Fehr'];  

$WriteMyRequest=
"<html><head><meta http-equiv='refresh' content='120' charset='UTF-8'></head><body>".
"<p> ".$TimeStamp."<p> The Humidity is Η σχετική υγρασία είναι: "       . $var1 . "% </p>".
"<p>And the Temperature is Η θερμοκρασία είναι : " . $var2 . " Celcius </p>".
"<p>And the Temperature is Η θερμοκρασία είναι: " . $var3 . " Fahreinheit</p>".
"<p>And The Heat Index is Ο δείκτης Θερμότητας είναι: "  . $var4 . " Heat Index Celcius </p>".
"<p>And The Heat Index is Ο δείκτης Θερμότητας είναι: "  . $var5 . " Heat Index Fahrenheit </p><br/>".
"</body></html>";


// file_put_contents('dataDisplayer.html', $WriteMyRequest, FILE_APPEND);  
file_put_contents('dataDisplayer.html', $WriteMyRequest);  


?>