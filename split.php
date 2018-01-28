<?php
    //$param = @$_REQUEST["name"]  
    //print $param
    //print  $s
    //echo $_POST["name"]


    
    //$cmd = "sudo  ./docextract-lib/a.out" . " \"" . $_POST["name"] . "\"";
    $cmd = "sudo ./nlp-lib/a.out" . " \"" . $_POST["name"] . "\"";
    
    //print $cmd;
    //print shell_exec("sudo ./a.out { _REQUEST['name']}")
    //print $cmd



    echo shell_exec($cmd);
    
    //$result = shell_exec($cmd);
    //$arr = array(
    //    "text"=> $_POST["name"],
    //    "result"=> $result
    //);
    
    //echo json_encode($arr, JSON_UNESCAPED_UNICODE);
?>
