package chevalun.integer {
	class ComplementInteger extends Integer {
		type T = ComplementInteger
		
		def this(s: String) = {
			this()
			setOrigin(s.toInt)
		}				
				
		def + (x: ComplementInteger): ComplementInteger = {
			new ComplementInteger(this.origin + x.origin)
		}
		
		def - (x: ComplementInteger): ComplementInteger = {
			new ComplementInteger(this.origin - x.origin)
		}
		
		def toInt: Int = {
			origin
		}
	}
}