<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>CaseShow 法务服务系统</title>

    <link rel="stylesheet" href="css/main.css">
</head>
<body>

<nav class="navbar navbar-inverse" role="navigation">
    <div class="container-fluid">
        <div class="navbar-header">
            <a class="navbar-brand" href="index.html">
                <img src="img/logo.png" >
            </a>
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#example-navbar-collapse">
                <span class="sr-only"> </span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
        </div>
        <div class="collapse navbar-collapse" id="example-navbar-collapse">
            <ul class="nav navbar-nav navbar-right">
                <li><a href="index.html">首页</a></li>
                <li class="dropdown">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#">
                        文书检索 <span class="caret"></span>
                    </a>
                    <ul class="dropdown-menu">
                        <li><a href="search.php">语义检索</a></li>

                        <!--<li class="divider"></li>-->
                        <li><a href="#">案由检索</a></li>

                        <!--<li class="divider"></li>-->
                        <li><a href="#">法院检索</a></li>
                    </ul>
                </li>
                <li><a href="#">法律条文</a></li>
                <li><a href="#">指导案例</a></li>
                <li class="active"><a href="nlp-tool.php">NLP工具</a></li>
                <li><a href="./about.html">关于我们</a></li>
            </ul>
        </div>
    </div>
</nav>

<script>
    var test = "Harvey";
</script>
<?php
    function httpPost($url,$params){
        $postData = '';
        //create name value pairs seperated by &
        foreach($params as $k => $v) { 
            $postData .= $k . '='.$v.'&'; 
        }
        $postData = rtrim($postData, '&');
      
        $ch = curl_init();  
      
        curl_setopt($ch,CURLOPT_URL,$url);
        curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
        curl_setopt($ch,CURLOPT_HEADER, false); 
        curl_setopt($ch, CURLOPT_POST, count($postData));
            curl_setopt($ch, CURLOPT_POSTFIELDS, $postData);    
      
        $output=curl_exec($ch);
      
        curl_close($ch);
        return $output;     
    }
?>


<main class="main">
    <div class="nlptool-input">
        <form method="post">
            <div class="input-group input-group-lg">
            <textarea  class="form-control" placeholder="请输入需要处理的文本" name="contents"><?php  echo $_POST["contents"];?></textarea>
            </div>

            <div class="fenxi-circle">
                   <input type="submit" value="分析">
            </div>
        </form>
    </div>

    <?php
        $params = array(
            "name" => $_POST["contents"]
        );
    
        $ResArray = json_decode(httpPost("http://localhost/split.php", $params), true);
        //echo httpPost("http://localhost/split.php", $params);
        //print_r($ResArray);

        $fenciResArray = $ResArray["fenciRes"]; 
        $fenciResStr = "";
        
        for($i = 0; $i < count($fenciResArray["words"]); $i++){
            if($fenciResArray["words"][$i] != "\r"){
                $fenciResStr = $fenciResStr . addslashes($fenciResArray["words"][$i]) . "/". addslashes($fenciResArray["type"][$i]) . "  "; 
            }  
        }

    ?>
        
    <script type="text/javascript">
        function show_fenciRes(){
            document.getElementById("tagscloud").style.display="none";
            document.getElementById("textarearesult").style.display="block";
            document.getElementById("textarearesult").value="<?php echo addslashes($fenciResStr);?>";
            //document.getElementById("nlptool-select-fenci").style.background="#5a5a5a";
            //document.getElementById("nlptool-select-fenci-mb").style.background="#5a5a5a";
            <?php $graph_show_name = "fenci"; ?>
        }

        function show_keywordsRes(){
            document.getElementById("tagscloud").style.display="none";
            document.getElementById("textarearesult").style.display="block";
            document.getElementById("textarearesult").value="<?php echo str_replace('#', '  ', $ResArray["keywordsRes"]); ?>";
            document.getElementById("textarearesult-mb").value="<?php echo str_replace('#', '  ', $ResArray["keywordsRes"]); ?>";
            //document.getElementById("nlptool-select-kewwords").style.background="#5a5a5a";
            //document.getElementById("nlptool-select-kewwords-mb").style.background="#5a5a5a";
            <?php $graph_show_name = "keywords"; ?>
        }
        
        function show_newwordsRes(){
            document.getElementById("tagscloud").style.display="none";
            document.getElementById("textarearesult").style.display="block";
            document.getElementById("textarearesult").value="<?php echo str_replace('#', '  ', $ResArray["newwordsRes"]); ?>";
            document.getElementById("textarearesult-mb").value="<?php echo str_replace('#', '  ', $ResArray["newwordsRes"]); ?>";
            //document.getElementById("nlptool-select-newwords").style.background="#5a5a5a";
            //document.getElementById("nlptool-select-newwords-mb").style.background="#5a5a5a";
            <?php $graph_show_name = "newwords"; ?>
        }
        
        function show_summaryRes(){
            document.getElementById("tagscloud").style.display="none";
            document.getElementById("textarearesult").style.display="block";
            document.getElementById("textarearesult").value="<?php echo $ResArray["summaryRes"]; ?>";
            document.getElementById("textarearesult-mb").value="<?php echo $ResArray["summaryRes"]; ?>";
            //document.getElementById("nlptool-select-summary").style.background="#5a5a5a";
            //document.getElementById("nlptool-select-summary-mb").style.background="#5a5a5a";
            <?php $graph_show_name = "summary"; ?>
            
            //document.form1.val.value = "Harvey";
            //document.form1.submit();

        if (window.XMLHttpRequest)
          {
            // IE7+, Firefox, Chrome, Opera, Safari 浏览器执行代码
            xmlhttp=new XMLHttpRequest();
          }
          else
          {
            // IE6, IE5 浏览器执行代码
            xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
          }
          xmlhttp.onreadystatechange=function()
          {
            if (xmlhttp.readyState==4 && xmlhttp.status==200)
            {
              document.getElementById("txtHint").innerHTML=xmlhttp.responseText;
            }
          }
          var str="XHG";
          xmlhttp.open("GET","./ajax.php?graph_type="+str,true);
          xmlhttp.send();
        }
        
        function show_graphRes(){
            document.getElementById("textarearesult").style.display="none";
            document.getElementById("tagscloud").style.display="block";
            //document.getElementById("tagscloud").innerHTML="<?php echo $fenciResStr_Graph;?>";
        }
    </script>


    <form name="form1"  method="post">
    <input type="hidden" name="val"  value="">  

    <!-- document.getElementById("textarearesult").value="<?php echo addslashes($fenciResStr);?>"; -->
    <div class="nlptool-result">
        <div class="nlptool-result-left">
            <div class="nlptool-select" id="nlptool-select-fenci-mb" onclick="show_fenciRes()">分词标注</div>
            <div class="nlptool-select" id="nlptool-select-freq-mb" onclick="show_()">词频统计</div>
            <div class="nlptool-select" id="nlptool-select-keywords-mb" onclick="show_keywordsRes()">抽关键词</div>
            <div class="nlptool-select" id="nlptool-select-shiti-mb" onclick="fun1()">实体抽取</div>
            <div class="nlptool-select" id="nlptool-select-newwords-mb" onclick="show_newwordsRes()">新词发现</div>
            <div class="nlptool-select" id="nlptool-select-summary-mb" onclick="show_summaryRes()">自动文摘</div>
        </div>
        <div class="nlptool-result-center">
            <div id="tagscloud">
                <?php
                    //print $_GET["graph_type"];
                    //print_r($_GET);
                    //print $_POST["val"];
                    //echo $graph_show_name;
                    //echo "\"+test+\"";
                    if($graph_show_name == "summary"){
                        $keywordsResArray = explode('#', $ResArray["keywordsRes"]);
                        //print_r($keywordsResArray);
                        $fenciResStr_Graph = "";
                        for($i = 0; $i < count($keywordsResArray); $i++){
                            $fenciResStr_Graph  .= "<a  class='tagc" . ($i % 5) . "'>" . $keywordsResArray[$i] ."</a>";
                        }
                        echo $fenciResStr_Graph;
                    }
                ?>
            </div>

            <textarea class="result" id="textarearesult" placeholder="NLP处理结果展示" readonly="readonly"><?php echo $fenciResStr; ?></textarea>
        </div>

        <div class="nlptool-result-right">
            <div>
                <div class="showmanner" onclick="show_graphRes()">图表</div>
                <div class="showmanner">文本</div>
            </div>
            <hr width=100% size=1 color=#00ffff style="margin-bottom:5px;FILTER: alpha(opacity=100,finishopacity=0,style=3)">
            <div>
                <label>分词标注</label>
                <p>
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法，
                </p>
            </div>

        </div>
    </div>

    <div class="fenxi-mb">
        <div class="nlptool-select-mb" id="nlptool-select-fenci"  onclick="show_fenciRes()"><div>分词标注</div></div>
        <div class="nlptool-select-mb" id="nlptool-select-freq" onclick=""><div>词频统计</div></div>
        <div class="nlptool-select-mb" id="nlptool-select-keywords" onclick="show_keywordsRes()"><div>抽关键词</div></div>
        <div class="nlptool-select-mb" id="nlptool-select-shiti" onclick=""><div>实体抽取</div></div>
        <div class="nlptool-select-mb" id="nlptool-select-newwords" onclick="show_newwordsRes()"><div>新词发现</div></div>
        <div class="nlptool-select-mb" id="nlptool-select-summary" onclick="show_summaryRes()"><div>自动文摘</div></div>
    </div>

    <div class="nlptool-result-mb">
        <div class="nlptool-result-mb-top">
            <div class="nlptool-result-mb-top-left">
                <p>
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法分词标注是基于模糊神经算法算法，
                </p>
            </div>
            <div class="nlptool-result-mb-top-right">
                <div class="mb-showmanner">文本</div>
                <div class="mb-showmanner">图表</div>
            </div>
        </div>
        <div class="nlptool-result-mb-buttom">
             <textarea class="mb-result" id="textarearesult-mb" placeholder="NLP处理结果展示" readonly="readonly" placeholder="处理结果展示"><?php
                    //$params = array(
                    //    "name" => $_POST["contents"]
                    //);
                    //echo httpPost("http://localhost/split.php", $params);
                    echo $fenciResStr;
             ?></textarea>
        </div>
    </div>

</main>


<footer class="panel-footer">
    <br>
    <a target="_blank" href="http://wenshu.court.gov.cn/">|中国裁判文书网|</a>
    <a target="_blank" href="http://www.ajxxgk.jcy.cn/html/index.html">人民检察院案件信息公开网|</a><br>
    <a target="_blank" href="http://www.court.gov.cn/zgsplcxxgkw/">|中国审判流程信息公开网|</a>
    <a target="_blank" href="http://shixin.court.gov.cn/">中国执行信息公开网|</a>
    <a target="_blank" href="http://ipr.court.gov.cn/">中国知识产权裁判文书网|</a>
    <a target="_blank" href="http://www.ccmt.org.cn/">中国涉外商事海事审判网|</a>

    <p>
        地址：辽宁省沈阳市浑南区南屏东路16号 电话：024-24696180 <br>
        中国科学院沈阳计算技术研究所 版权所有<br><br>
        辽ICP备18002117号-1
    </p>
</footer>

<script src="js/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
<script src="js/xun.js"></script>


</body>
</html>
