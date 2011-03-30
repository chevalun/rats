package chevalun.integer {
	trait IntegerTraits {
		type T
		def +(x: T): T
		def -(x: T): T
		def toInt: Int
	}
	
	abstract class Integer extends IntegerTraits {
		var origin: Int = 0
		
		override def toString: String = {
			return this.toInt.toString
		}
		
		protected def setOrigin(v: Int) = {
			origin = v
		}
		
		protected def this(v: Int) = {
			this()
			setOrigin(v)
		}
	}
}