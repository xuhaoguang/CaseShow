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
                        <li><a href="#">语义检索</a></li>

                        <!--<li class="divider"></li>-->
                        <li><a href="#">案由检索</a></li>

                        <!--<li class="divider"></li>-->
                        <li><a href="#">法院检索</a></li>
                    </ul>
                </li>
                <li><a href="#">法律条文</a></li>
                <li><a href="#">指导案例</a></li>
                <li class="active"><a href="nlp-tool.php">NLP工具</a></li>
                <!--<li class="dropdown">-->
                    <!--<a class="dropdown-toggle" data-toggle="dropdown" href="#">-->
                        <!--NLP工具 <span class="caret"></span>-->
                    <!--</a>-->
                    <!--<ul class="dropdown-menu">-->
                        <!--<li><a href="#">在线分词</a></li>-->

                        <!--&lt;!&ndash;<li class="divider"></li>&ndash;&gt;-->
                        <!--<li><a href="#">抽关键词</a></li>-->

                    <!--</ul>-->
                <!--</li>-->
                <li><a href="#">关于我们</a></li>
            </ul>
        </div>
    </div>
</nav>

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

    <div class="nlptool-result">
        <div class="nlptool-result-left">
            <a href="#"><div class="nlptool-select">分词标注</div></a>
            <a href="#"><div class="nlptool-select">词频统计</div></a>
            <a href="#"><div class="nlptool-select">抽关键词</div></a>
            <a href="#"><div class="nlptool-select">实体抽取</div></a>
            <a href="#"><div class="nlptool-select">文本分类</div></a>
            <a href="#"><div class="nlptool-select">自动文摘</div></a>
        </div>
        <div class="nlptool-result-center">
            <textarea class="result"  placeholder="NLP处理结果展示" readonly="readonly"><?php
                    $params = array(
                        "name" => $_POST["contents"]
                    );
                    echo httpPost("http://localhost/split.php", $params);
                ?></textarea>
        </div>

        <div class="nlptool-result-right">
            <div>
                <a href="#"><div class="showmanner">图表</div></a>
                <a href="#"><div class="showmanner">文本</div></a>
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
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
        <a href="#"><div class="nlptool-select-mb"><div>分词标注</div></div></a>
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
             <textarea class="mb-result" placeholder="NLP处理结果展示" readonly="readonly" placeholder="处理结果展示"><?php
                    $params = array(
                        "name" => $_POST["contents"]
                    );
                    echo httpPost("http://localhost/split.php", $params);
             ?></textarea>
        </div>
    </div>

</main>

<footer class="panel-footer">
    <br>
    <a>|中国裁判文书网|</a>
    <a>任命检察院案件信息公开网|</a><br>
    <a>|中国审判流程信息公开网|</a>
    <a>中国执行信息公开网|</a>
    <a>中国知识产权裁判文书网|</a>
    <a>中国涉外商事海事审判网|</a>
    <p>
        地址：辽宁省沈阳市浑南区南屏东路16号 电话：024-24696180 <br>
        中国科学院沈阳计算技术研究所 版权所有
    </p>
</footer>


<!--<script src="http://libs.useso.com/js/jquery/2.1.1/jquery.min.js" type="text/javascript"></script>-->
<!--<script>window.jQuery || document.write('<script src="js/jquery-2.1.1.min.js"><\/script>')</script>-->
<!--<script src="http://libs.useso.com/js/bootstrap/3.2.0/js/bootstrap.min.js"></script>-->

<script src="js/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>


</body>
</html>
