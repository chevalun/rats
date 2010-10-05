Raphael.fn.polyarea = (points) ->
	p = "M".concat(points[0].x, ",", points[0].y, "L")
	for i in [1..points.length - 1]
		p = p.concat(points[i].x, ",", points[i].y, " ")
	p = p.concat(points[0].x, ",", points[0].y, "z")
	return this.path(p);

Array::top = ->
	this[this.length-1]

class Polygon
	constructor: (@startX, @startY, @paper) ->
		@finished = false
		@points = [{x: @startX, y: @startY}]
		@startPoint = @paper.circle(@startX, @startY, 5).attr(fill: "red")
		@startPoint.hover(
			(event) ->
				this.scale(1.2, 1.2)
			(event) ->
				this.scale(1, 1)
		)
		@startPoint.click f = (event) =>
			@addPoint(@startX, @startY)
			@finished = true
			mark = @paper.polyarea(@points).attr("fill": "blue", "fill-opacity": 0.1)
			mark.hover(
				(event) ->
					this.attr("fill-opacity": 0.5)
				(event) ->
					this.attr("fill-opacity": 0.1)
			)
			mark.click(clickCallback)
			@startPoint.unclick(f)
			
	addPoint: (posX, posY) ->
		tail = @points.top()
		@paper.line(tail.x, tail.y, posX, posY)
		@points.push x: posX, y: posY
				
	isFinished: ->
		@finished

currertPoly = null

clickCallback = (event) ->
	x = event.layerX
	y = event.layerY
	if currertPoly == null || currertPoly.isFinished()
		currertPoly = new Polygon(x, y, paper)
	else
		currertPoly.addPoint(x, y)

paper = Raphael("test", 500, 375)
image = paper.image("moter.jpg", 0, 0, 500, 375)
image.click clickCallback