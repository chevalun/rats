(function() {
  var paper;
  paper = Raphael("test", 640, 264);
  $('[name=submit-danmaku]').click(function() {
    paper.text(30, Math.floor(Math.random() * 264), $('[name=danmaku-text]').val()).attr({
      'font-size': 30,
      'fill': 'white'
    }).animate({
      'x': 700
    }, 2000);
    return $('[name=danmaku-text]').val();
  });
})();
