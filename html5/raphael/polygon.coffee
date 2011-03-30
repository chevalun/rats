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
		@lines = []
		@points = [{x: @startX, y: @startY}]
		@startPoint = @paper.circle(@startX, @startY, 5).attr(fill: "red")
		@startPoint.hover(
			(event) ->
				this.scale(1.2, 1.2)
			(event) ->
				this.scale(1, 1)
		)
		@startPoint.click f = (event) =>
			@finish()
			@startPoint.unclick(f)
	
	
	finish: ->
		if @points.length > 2
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

	undo: ->
		if @lines.length > 0
			@lines.pop().remove()
			@points.pop()
				
	addPoint: (posX, posY) ->
		tail = @points.top()
		@lines.push @paper.line(tail.x, tail.y, posX, posY)
		@points.push x: posX, y: posY
				
	isFinished: ->
		@finished

currentPoly = null

clickCallback = (event) ->
	x = event.layerX
	y = event.layerY
	if currentPoly == null || currentPoly.isFinished()
		currentPoly = new Polygon(x, y, paper)
	else
		currentPoly.addPoint(x, y)

fin = new HotKey('f', (event) ->
	if currentPoly != null && !currentPoly.isFinished()
		currentPoly.finish()
)

undo = new HotKey('u', (event) ->
	if currentPoly != null && !currentPoly.isFinished()
		currentPoly.undo()
)

paper = Raphael("test", 500, 375)
image = paper.image("moter.jpg", 0, 0, 500, 375)
image.click clickCallback
