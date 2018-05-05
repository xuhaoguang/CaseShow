<?php
    //print $param
    //print  $s
    //echo $_POST["name"];


    
    //$cmd = "sudo  ./docextract-lib/a.out" . " \"" . $_POST["name"] . "\"";
    $cmd = "sudo ./nlp-lib/a.out" . " \"" . addcslashes(str_replace("n", "",$_POST["name"]), '",\\, \r\n') . "\"";
    //$cmd = "sudo ./nlp-lib/a.out" . " \"" . str_replace("n", "", addcslashes($_POST["name"], '",\\, \r\n')). "\"";
    
    //print $cmd;
    //print shell_exec("sudo ./a.out { _REQUEST['name']}")
    //print $cmd



    echo shell_exec($cmd);
    
    //$result = shell_exec($cmd);
    //$arr = array(
    //    "text"=> $_POST["name"],
    //    "result"=> $result
    //);
    
    //echo json_encode($result, JSON_UNESCAPED_UNICODE);
?>
