package com.glumes.openglbasicshape.activitiy

import com.glumes.openglbasicshape.R
import com.glumes.openglbasicshape.base.BaseRenderActivity
import com.glumes.openglbasicshape.draw.texture.*

class TextureActivity : BaseRenderActivity() {


    override fun initShapeClass() {
        shapeClazzArray.put(R.id.tirangle_texture, TriangleTexture::class.java)
        shapeClazzArray.put(R.id.rectangle_texture, RectangleTexture::class.java)
        shapeClazzArray.put(R.id.circle_texture, CircleTexture::class.java)
        shapeClazzArray.put(R.id.multi_texture, MultiTexture::class.java)
        shapeClazzArray.put(R.id.cube_texture, CubeTexture2::class.java)

    }

    override fun setMenuId() {
        setToolbarMenu(R.menu.basic_texture_menu)
    }

    override fun setInitShape() {
        super.setInitShape()
        mRenderer.setShape(TriangleTexture::class.java)
    }
}
