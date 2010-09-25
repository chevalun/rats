package chevalun.integer {
	object ConvertHelper {
		val shiftOffset = 0x80000000
		
		def stringToShift(s: String): Int = {
			s.toInt ^ shiftOffset
		}
	}
}