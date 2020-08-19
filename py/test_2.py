import truetypetracer as ttt


def test_seg_writer():
    #wr = ttt.NGC_Writer()
    wr = ttt.SEG_Writer()

    # wr.scale = 1
    wr.arc = False
    wr.conic = False
    wr.cubic = False
    s3 = ttt.ttt("LT", wr)
    print(s3)
    s = wr.get_segments()
    print(s)
    e = wr.extents
    print("number of segments %s" % len(s))
    print(e)
    print("extents max x %s" % e.maxx)
    print("extents min x %s" % e.minx)
    print("extents max y %s" % e.maxy)
    print("extents min y %s" % e.miny)
