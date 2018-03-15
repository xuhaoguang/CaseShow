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
                <form>
                    <div class="search-left-label">案件类型</div>

                    <select class="selectpicker">
                        <option value="volvo">婚姻家庭纠纷</option>
                        <option value="saab">劳动争议纠纷</option>
                        <option value="opel">公司财产纠纷</option>
                        <option value="audi">公共安全纠纷</option>
                    </select>

                    <div class="search-left-label">案情描述</div>

                    <textarea  placeholder="请输入用户个人案情" name="contents"></textarea>

                    <input type="submit" class="submit" value="查找相似案例">
                </form>

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
                <div class="wenshu-title"><a href="wenshu-info.php" target="_blank">史某与谷某甲离婚纠纷一审民事判决书</a></div>
                <div>
                    <div class="wenshu-court">宿州市埇桥区人民法院</div>
                    <div class="wenshu-time">2015-09-25</div>
                    <div class="wenshu-similarity">相似度：0.91</div>
                </div>

                <hr class="wenshu-hr">
                <div class="wenshu-reason">[裁判理由]</div>
                <div class="wenshu-reason-info">
                    本院认为，原、被告经婚姻登记机关登记结婚，其婚姻关系合法有效。在共同生活期间，原、被告的夫妻感情尚可，生育一子。原告称被告自私、暴躁，处事易走极端。2014年12月26日开始，原告通过被告的手机才发现被告与异性有暧昧关系且已...
                </div>


                <div class="wenshu-title"><a>原告梁某某与被告刘某某离婚纠纷一审民事判决书</a></div>
                <div>
                    <div class="wenshu-court">永新县人民法院</div>
                    <div class="wenshu-time">2015-12-21</div>
                    <div class="wenshu-similarity">相似度：0.88</div>
                </div>

                <hr class="wenshu-hr">
                <div class="wenshu-reason">[裁判理由]</div>
                <div class="wenshu-reason-info">
                    本院认为，证据1不能反映被告使用暴力、胁迫等手段带走原告，结合被告的质证意见，可以反映双方就是否继续共同生活进行协商，但未果，故对证据1的拟证目的不予采信。证据2、3，被告未提出异议，本院予以确认。,被告刘某某辩称，被告...
                </div>


                <div class="wenshu-title">徐某与覃某离婚纠纷一审民事判决书</div>
                <div>
                    <div class="wenshu-court">山西省方山县人民法院</div>
                    <div class="wenshu-time">2016-09-05</div>
                    <div class="wenshu-similarity">相似度：0.83</div>
                </div>

                <hr class="wenshu-hr">
                <div class="wenshu-reason">[裁判理由]</div>
                <div class="wenshu-reason-info">
                    本院认为，被告覃某与原告徐某均系再婚，婚姻存续期间不到一年，且因琐事闹到派出所，感情淡薄，被告覃某自2013年5月12日外出至今无音讯，婚姻名存实亡。故对原告徐某的离婚请求，本院予以支持。原、被告双方如果有财产纠纷，可另案...
                </div>

                <div class="wenshu-title">潘某甲与李某某离婚纠纷一审民事判决书</div>
                <div>
                    <div class="wenshu-court">四川省梓潼县人民法院</div>
                    <div class="wenshu-time">2017-01-14</div>
                    <div class="wenshu-similarity">相似度：0.79</div>
                </div>

                <hr class="wenshu-hr">
                <div class="wenshu-reason">[裁判理由]</div>
                <div class="wenshu-reason-info">
                    本院认为：原、被告婚前相识时间较短，便仓促结婚，彼此性格了解较少，在婚后生活中，双方又长期在外务工，造成夫妻分居时间较长，感情交流较少。节假日相聚时，夫妻间又常发生争吵，给子女身心造成伤害。原告在短时间内又再次起诉离婚...
                </div>



                <!--<div style="width: 100%; background-color: aqua">-->
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

            </div>

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

