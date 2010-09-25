package chevalun.integer {
	class BcdInteger(v: Int) extends Integer(v: Int) {
		type T = BcdInteger

		origin = v
		
		def + (x: BcdInteger): BcdInteger = {
			return new BcdInteger(this.origin + x.origin)
		}
		
		def - (x: BcdInteger): BcdInteger = {
			return new BcdInteger(this.origin - x.origin)
		}
		
		override def toString: String = {
			return origin.toString
		}
	}
}