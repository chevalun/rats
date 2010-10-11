(function() {
  var Polygon, clickCallback, currertPoly, image, paper;
  var __bind = function(func, context) {
    return function(){ return func.apply(context, arguments); };
  };
  Raphael.fn.polyarea = function(points) {
    var i, p;
    p = "M".concat(points[0].x, ",", points[0].y, "L");
    for (i = 1; (1 <= points.length - 1 ? i <= points.length - 1 : i >= points.length - 1); (1 <= points.length - 1 ? i += 1 : i -= 1)) {
      p = p.concat(points[i].x, ",", points[i].y, " ");
    }
    p = p.concat(points[0].x, ",", points[0].y, "z");
    return this.path(p);
  };
  Array.prototype.top = function() {
    return this[this.length - 1];
  };
  Polygon = function(_a, _b, _c) {
    var f;
    this.paper = _c;
    this.startY = _b;
    this.startX = _a;
    this.finished = false;
    this.points = [
      {
        x: this.startX,
        y: this.startY
      }
    ];
    this.startPoint = this.paper.circle(this.startX, this.startY, 5).attr({
      fill: "red"
    });
    this.startPoint.hover(function(event) {
      return this.scale(1.2, 1.2);
    }, function(event) {
      return this.scale(1, 1);
    });
    this.startPoint.click(f = __bind(function(event) {
      this.finish();
      return this.startPoint.unclick(f);
    }, this));
    return this;
  };
  Polygon.prototype.finish = function() {
    var mark;
    this.addPoint(this.startX, this.startY);
    this.finished = true;
    mark = this.paper.polyarea(this.points).attr({
      "fill": "blue",
      "fill-opacity": 0.1
    });
    mark.hover(function(event) {
      return this.attr({
        "fill-opacity": 0.5
      });
    }, function(event) {
      return this.attr({
        "fill-opacity": 0.1
      });
    });
    return mark.click(clickCallback);
  };
  Polygon.prototype.addPoint = function(posX, posY) {
    var tail;
    tail = this.points.top();
    this.paper.line(tail.x, tail.y, posX, posY);
    return this.points.push({
      x: posX,
      y: posY
    });
  };
  Polygon.prototype.isFinished = function() {
    return this.finished;
  };
  currertPoly = null;
  clickCallback = function(event) {
    var x, y;
    x = event.layerX;
    y = event.layerY;
    return currertPoly === null || currertPoly.isFinished() ? (currertPoly = new Polygon(x, y, paper)) : currertPoly.addPoint(x, y);
  };
  paper = Raphael("test", 500, 375);
  image = paper.image("moter.jpg", 0, 0, 500, 375);
  image.click(clickCallback);
})();
