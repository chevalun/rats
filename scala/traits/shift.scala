package chevalun.integer {
	class ShiftInteger(v: Int) extends Integer(v: Int) {
		type T = ShiftInteger
		
		def this (s: String) = this( ConvertHelper.stringToShift(s) )
		
		def + (x: ShiftInteger): ShiftInteger = {
			new ShiftInteger(this.origin + x.origin)
		}
		
		def - (x: ShiftInteger): ShiftInteger = {
			new ShiftInteger(this.origin - x.origin)
		}
		
		override def toInt: Int = {
			origin ^ ConvertHelper.shiftOffset
		}
	}
}