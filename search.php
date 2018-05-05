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
                <li class="dropdown active">
                    <a class="dropdown-toggle" data-toggle="dropdown" href="#">
                        文书检索 <span class="caret"></span>
                    </a>
                    <ul class="dropdown-menu">
                        <li><a href="search.php">语义检索</a></li>
                        <li><a href="#">案由检索</a></li>
                        <li><a href="#">法院检索</a></li>
                    </ul>
                </li>
                <li><a href="#">法律条文</a></li>
                <li><a href="#">指导案例</a></li>
                <li><a href="nlp-tool.php">NLP工具</a></li>
                <li><a href="about.html">关于我们</a></li>
            </ul>
        </div>
    </div>
</nav>


<main class="main">
    <div class="row">
        <div class="col-md-1"></div>

        <div class="col-md-3">
            <div class="search-left">
                <form method="post">
                    <div class="search-left-label">案件类型</div>

                    <select name="wenshu_type" class="selectpicker">
                        <option value="婚姻家庭纠纷" <?php if($_POST["wenshu_type"] == "婚姻家庭纠纷") echo "selected = selected" ?> >婚姻家庭纠纷</option>
                        <option value="财产经济纠纷" <?php if($_POST["wenshu_type"] == "财产经济纠纷") echo "selected = selected" ?>>财产经济纠纷</option>
                        <option value="劳动争议纠纷" <?php if($_POST["wenshu_type"] == "劳动争议纠纷") echo "selected = selected" ?>>劳动争议纠纷</option>
                        <option value="公共安全纠纷" <?php if($_POST["wenshu_type"] == "公共安全纠纷") echo "selected = selected" ?>>公共安全纠纷</option>
                    </select>

                    <div class="search-left-label">案情描述</div>

                    <textarea  placeholder="请输入用户个人案情" name="wenshu_contents"><?php echo $_POST["wenshu_contents"]; ?></textarea>

                    <input type="submit" class="submit" value="查找相似案例">
                </form>
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

    $params = array(
            "wenshu_type" => $_POST["wenshu_type"],
            "wenshu_contents" => $_POST["wenshu_contents"]
    );

    //print_r($params);
    $Res = json_decode(httpPost("http://localhost/deal_search.php", $params), true);
    //print_r($Res);
    //echo httpPost("http://localhost/deal_search.php", $params);
?>

                    <div class="result">
                    <div class="result-1">查找结果</div>
                        <div>
                            <div class="result-2">
                                <div class="result-3">相似案例：</div>
                                <div class="result-3">高度相似：</div>
                                <div class="result-3">计算耗时：</div>
                            </div>
                            <div class="result-2">
                                <div class="result-4">1288条</div>
                                <div class="result-4">21条</div>
                                <div class="result-4">1500毫秒</div>
                            </div>
                        </div>
                    </div>

            </div>
        </div>

        <!--本人经人介绍与现任丈夫相识，交往不久后在深圳市福田区民政局登记结婚。因性格不合，双方经常争吵。不但如此，丈夫的人品存在极大问题：说谎、不尊重长辈、时常侮辱诽谤本人。2013年8月下旬，双方因感情不和正式分居，在此后的短信沟通中，丈夫也认为这场婚姻名存实亡-->
        <div class="col-md-7">
            <div class="search-right">
            <?php
                $arrlength=count($Res);
                for($i=0; $i<$arrlength; $i++){
                    echo '<div class="wenshu-title"><a href="wenshu_pdf/' . $Res[$i]["docid"] .'.pdf" target="_blank">' .$Res[$i]["name"] .'</a></div>';
                    echo '<div>';
                        echo '<div class="wenshu-court">' . $Res[$i]["court"] .'</div>';
                        echo '<div class="wenshu-time">'. $Res[$i]["date"] .'</div>';
                        echo '<div class="wenshu-download-img"> <a href="wenshu_doc/' . $Res[$i]["docid"] .'.doc"><img src="img/download_small.png"/></a></div>';
                        echo '<div class="wenshu-similarity"> 相似度:' . $Res[$i]["score"] .'</div>';
                    echo '</div>';
                    echo '<hr class="wenshu-hr">';
                    echo '<div class="wenshu-reason">[裁判理由]</div>';
                    echo '<div class="wenshu-reason-info">';
                    #echo $Res[$i]["name"] . $Res[$i]["name"] . $Res[$i]["name"]  . $Res[$i]["name"]; 
                    echo $Res[$i]["user_contents"];
                    echo '</div>';
                } 
            ?>

                <!--<div style="width: 100%; background-color: aqua">-->
                <!--    
                    <ul class="pagination">
                        <li>
                            <a href="#">上一页</a>
                        </li>
                        <li>
                            <a href="#">1</a>
                        </li>
                        <li>
                            <a href="#">2</a>
                        </li>
                        <li>
                            <a href="#">3</a>
                        </li>
                        <li>
                            <a href="#">4</a>
                        </li>
                        <li>
                            <a href="#">5</a>
                        </li>
                        <li>
                            <a href="#">下一页</a>
                        </li>
                    </ul>
                -->
                
        </div>
        <div class="col-md-1"></div>
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


</body>
</html>

