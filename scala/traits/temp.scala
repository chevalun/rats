abstract class Father {
	var value: Int = 0
	
	protected def setValue(v: Int) = {
		value = v
	}
	
	protected def this(v: Int) = {
		this()
		setValue(v)
	}
}

class Child extends Father {
}

val a = new Child(42)