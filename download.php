<?php
    $file_name="wenshu.zip";
    //如果文件名是中文的话，则要把utf-8编码（源程序文件filedown.php的编码）转换为//gb2312编码，使用下面一句即可
    $file_name=iconv("utf-8","gb2312",$file_name);
    if(!file_exists($file_name)){
        echo "文件不存在!";
        return ;
    }
    $fp=fopen($file_name,"r");
    $file_size=filesize($file_name);//文件大小
    //告诉浏览器返回的是文件类型
    header("Content-type: application/octet-stream;charset=utf-8");
    //告诉浏览器返回内容是按照字节返回的
    header("Accept-Ranges:bytes");
    //告诉浏览器文件的大小
    header("Accept-Length:".$file_size);
    //告诉浏览器下载文件时弹出的对话框中的文件名
    header("Content-Disposition:attachment;filename=".$file_name);
    
    //向客户端返回数据
    $buffer=1024;
    //为了下载安全，做一个文件字节读取计数器
    $file_count=0;
    while(!feof($fp)&&($file_size-$file_count>0)){
        $file_data=fread($fp,$buffer);
        $file_count+=$buffer;
        echo $file_data;
    }
    fclose($fp);
?>
