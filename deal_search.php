<?php
    //print $_POST["wenshu_type"];
    //print $_POST["wenshu_contents"];
    
    //$arr = array(
    //    "text"=> $_POST["wenshu_type"],
    //);

    //echo $_POST["wenshu_type"];


    $cmd = "sudo python search_res.py" . " \"" . addcslashes(str_replace("n", "",$_POST["wenshu_contents"]), '",\\, \r\n') . "\"";
    #$cmd = "sudo python search_res.py " . $_POST["wenshu_contents"];

    //echo "12345678";
    
    
    echo shell_exec($cmd);
    //echo json_encode($result, JSON_UNESCAPED_UNICODE);

?>
