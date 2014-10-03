package simulations

import org.scalatest.FunSuite

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

@RunWith(classOf[JUnitRunner])
class CircuitSuite extends CircuitSimulator with FunSuite {
  val InverterDelay = 1
  val AndGateDelay = 3
  val OrGateDelay = 5
  
  test("andGate example") {
    val in1, in2, out = new Wire
    andGate(in1, in2, out)
    in1.setSignal(false)
    in2.setSignal(false)
    run
    
    assert(out.getSignal === false, "and 1")

    in1.setSignal(true)
    run
    
    assert(out.getSignal === false, "and 2")

    in2.setSignal(true)
    run
    
    assert(out.getSignal === true, "and 3")
  }

  test("orGate example") {
    val in1, in2, out = new Wire
    orGate(in1, in2, out)
    in1.setSignal(false)
    in2.setSignal(false)
    run

    assert(out.getSignal === false, "or 1")

    in1.setSignal(true)
    run

    assert(out.getSignal === true, "or 2")

    in2.setSignal(true)
    run

    assert(out.getSignal === true, "or 3")

    in1.setSignal(false)
    run

    assert(out.getSignal === true, "or 4")
  }

  test("orGate2 example") {
    val in1, in2, out = new Wire
    orGate2(in1, in2, out)
    in1.setSignal(false)
    in2.setSignal(false)
    run

    assert(out.getSignal === false, "or 1")

    in1.setSignal(true)
    run

    assert(out.getSignal === true, "or 2")

    in2.setSignal(true)
    run

    assert(out.getSignal === true, "or 3")

    in1.setSignal(false)
    run

    assert(out.getSignal === true, "or 4")
  }

  test("demux small") {
    val in, out = new Wire
    demux(in, Nil, out :: Nil)

    run
    assert(out.getSignal === false)

    in.setSignal(true)
    run
    assert(out.getSignal === true)
  }

  test("demux medium") {
    val in, c0, c1, o0, o1, o2, o3 = new Wire
    val c = c1 :: c0 :: Nil
    val o = o3 :: o2 :: o1 :: o0 :: Nil
    demux(in, c, o)

    run
    assert(o3.getSignal === false, 0)
    assert(o2.getSignal === false, 1)
    assert(o1.getSignal === false, 2)
    assert(o0.getSignal === false, 3)

    in.setSignal(true)
    run
    assert(o3.getSignal === false, 0)
    assert(o2.getSignal === false, 1)
    assert(o1.getSignal === false, 2)
    assert(o0.getSignal === true, 3)

    c0.setSignal(true)
    run
    assert(o3.getSignal === false, 0)
    assert(o2.getSignal === false, 1)
    assert(o1.getSignal === true, 2)
    assert(o0.getSignal === false, 3)

    c1.setSignal(true)
    run
    assert(o3.getSignal === true, 0)
    assert(o2.getSignal === false, 1)
    assert(o1.getSignal === false, 2)
    assert(o0.getSignal === false, 3)

    c0.setSignal(false)
    run
    assert(o3.getSignal === false, 0)
    assert(o2.getSignal === true, 1)
    assert(o1.getSignal === false, 2)
    assert(o0.getSignal === false, 3)
  }

}
