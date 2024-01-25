static const float zero[4] = { 0, 0, 0, 0 };
static const float one[4] = { 1, 1, 1, 1 };
static const float negOne[4] = { -1, -1, -1, -1 };

/*
=========================================================================================

GENERAL INTERACTION RENDERING

=========================================================================================
*/

/*
==================
RB_GLSL_DrawInteraction
==================
*/
void	RB_GLSL_DrawInteraction(const drawInteraction_t *din)
{
	// load all the vertex program parameters
	GL_UniformMatrix4fv(offsetof(shaderProgram_t, textureMatrix), mat4_identity.ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, localLightOrigin), din->localLightOrigin.ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, localViewOrigin), din->localViewOrigin.ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, lightProjectionS), din->lightProjection[0].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, lightProjectionT), din->lightProjection[1].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, lightProjectionQ), din->lightProjection[2].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, lightFalloff), din->lightProjection[3].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, bumpMatrixS), din->bumpMatrix[0].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, bumpMatrixT), din->bumpMatrix[1].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, diffuseMatrixS), din->diffuseMatrix[0].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, diffuseMatrixT), din->diffuseMatrix[1].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, specularMatrixS), din->specularMatrix[0].ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, specularMatrixT), din->specularMatrix[1].ToFloatPtr());

	switch (din->vertexColor) {
		case SVC_MODULATE:
			GL_Uniform4fv(offsetof(shaderProgram_t, colorModulate), one);
			GL_Uniform4fv(offsetof(shaderProgram_t, colorAdd), zero);
			break;
		case SVC_INVERSE_MODULATE:
			GL_Uniform4fv(offsetof(shaderProgram_t, colorModulate), negOne);
			GL_Uniform4fv(offsetof(shaderProgram_t, colorAdd), one);
			break;
		case SVC_IGNORE:
		default:
			GL_Uniform4fv(offsetof(shaderProgram_t, colorModulate), zero);
			GL_Uniform4fv(offsetof(shaderProgram_t, colorAdd), one);
			break;
	}

	// set the constant colors
	GL_Uniform4fv(offsetof(shaderProgram_t, diffuseColor), din->diffuseColor.ToFloatPtr());
	GL_Uniform4fv(offsetof(shaderProgram_t, specularColor), din->specularColor.ToFloatPtr());

	// material may be NULL for shadow volumes
	GL_Uniform1fv(offsetof(shaderProgram_t, specularExponent), &r_specularExponent);

	// set the textures

	// texture 0 will be the per-surface bump map
	GL_SelectTextureNoClient(0);
	din->bumpImage->Bind();

	// texture 1 will be the light falloff texture
	GL_SelectTextureNoClient(1);
	din->lightFalloffImage->Bind();

	// texture 2 will be the light projection texture
	GL_SelectTextureNoClient(2);
	din->lightImage->Bind();

	// texture 3 is the per-surface diffuse map
	GL_SelectTextureNoClient(3);
	din->diffuseImage->Bind();

	// texture 4 is the per-surface specular map
	GL_SelectTextureNoClient(4);
	din->specularImage->Bind();

#ifdef _SHADOW_MAPPING
	if(r_shadowMapping)
	{
		RB_ShadowMappingInteraction_setupMVP(din);

		// texture 6 is the shadow map
		GL_SelectTextureNoClient(6);
		RB_ShadowMappingInteraction_bindTexture();
	}
#endif

	GL_SelectTextureNoClient(0); //k2023

	// draw it
	RB_DrawElementsWithCounters(din->surf->geo);
}


/*
=============
RB_GLSL_CreateDrawInteractions

=============
*/
void RB_GLSL_CreateDrawInteractions(const drawSurf_t *surf)
{
	if (!surf) {
		return;
	}

	// perform setup here that will be constant for all interactions
	GL_State(GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE |
			GLS_DEPTHMASK | //k: fix translucent interactions
			backEnd.depthFunc);

	// bind the vertex and fragment shader
	if(r_usePhong)
		GL_UseProgram(&interactionShader);
	else
		GL_UseProgram(&interactionBlinnPhongShader);

	// enable the vertex arrays
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_TexCoord));
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_Tangent));
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_Bitangent));
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_Normal));
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_Vertex));	// gl_Vertex
	GL_EnableVertexAttribArray(offsetof(shaderProgram_t, attr_Color));	// gl_Color

	// texture 5 is the specular lookup table
	GL_SelectTextureNoClient(5);
	globalImages->specularTableImage->Bind();

	backEnd.currentSpace = NULL; //k2023

	for (; surf ; surf=surf->nextOnLight) {
		// perform setup here that will not change over multiple interaction passes

		// set the modelview matrix for the viewer
		/*float   mat[16];
		myGlMultMatrix(surf->space->modelViewMatrix, backEnd.viewDef->projectionMatrix, mat);
		GL_UniformMatrix4fv(offsetof(shaderProgram_t, modelViewProjectionMatrix), mat);*/ //k2023

		// set the vertex pointers
		idDrawVert	*ac = (idDrawVert *)vertexCache.Position(surf->geo->ambientCache);

		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Normal), 3, GL_FLOAT, false, sizeof(idDrawVert), ac->normal.ToFloatPtr());
		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Bitangent), 3, GL_FLOAT, false, sizeof(idDrawVert), ac->tangents[1].ToFloatPtr());
		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Tangent), 3, GL_FLOAT, false, sizeof(idDrawVert), ac->tangents[0].ToFloatPtr());
		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_TexCoord), 2, GL_FLOAT, false, sizeof(idDrawVert), ac->st.ToFloatPtr());

		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Vertex), 3, GL_FLOAT, false, sizeof(idDrawVert), ac->xyz.ToFloatPtr());
		GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Color), 4, GL_UNSIGNED_BYTE, false, sizeof(idDrawVert), ac->color);

		// this may cause RB_GLSL_DrawInteraction to be exacuted multiple
		// times with different colors and images if the surface or light have multiple layers
		RB_CreateSingleDrawInteractions(surf, RB_GLSL_DrawInteraction);
	}

	backEnd.currentSpace = NULL; //k2023

	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_TexCoord));
	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_Tangent));
	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_Bitangent));
	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_Normal));
	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_Vertex));	// gl_Vertex
	GL_DisableVertexAttribArray(offsetof(shaderProgram_t, attr_Color));	// gl_Color

	// disable features
	GL_SelectTextureNoClient(5);
	globalImages->BindNull();

	GL_SelectTextureNoClient(4);
	globalImages->BindNull();

	GL_SelectTextureNoClient(3);
	globalImages->BindNull();

	GL_SelectTextureNoClient(2);
	globalImages->BindNull();

	GL_SelectTextureNoClient(1);
	globalImages->BindNull();

	backEnd.glState.currenttmu = -1;
	GL_SelectTexture(0);

	GL_UseProgram(NULL);
}

/*
==================
RB_GLSL_DrawInteractions
==================
*/
void RB_GLSL_DrawInteractions(void)
{
	viewLight_t		*vLight;
	const idMaterial	*lightShader;

	//GL_SelectTexture(0); //k2023
	/* current
     * GL_STENCIL_TEST enabled
     * GL_BLEND enabled
     */

#ifdef _SHADOW_MAPPING
	const bool ShadowMapping = r_shadowMapping && r_shadows.GetBool();
	float clearColor[4];
	if(ShadowMapping)
	{
		RB_getClearColor(clearColor);
		if(r_dumpShadowMapFrontEnd)
		{
			r_dumpShadowMap = true;
			r_dumpShadowMapFrontEnd = false;
		}
	}
#ifdef _CONTROL_SHADOW_MAPPING_RENDERING
	const bool PureShadowMapping = ShadowMapping && r_shadowMappingScheme == SHADOW_MAPPING_PURE;
#endif
#endif

#ifdef _TRANSLUCENT_STENCIL_SHADOW
	const bool TranslucentStencilShadow = r_translucentStencilShadow && r_shadows.GetBool() && r_stencilShadowAlpha > 0.0f;
#endif
	//
	// for each light, perform adding and shadowing
	//
	for (vLight = backEnd.viewDef->viewLights ; vLight ; vLight = vLight->next) 
	{
		backEnd.vLight = vLight;

		// do fogging later
		if (vLight->lightShader->IsFogLight()) {
			continue;
		}

		if (vLight->lightShader->IsBlendLight()) {
			continue;
		}

		if (!vLight->localInteractions && !vLight->globalInteractions
		    && !vLight->translucentInteractions) {
			continue;
		}

		lightShader = vLight->lightShader;

		// clear the stencil buffer if needed
		if ((vLight->globalShadows || vLight->localShadows)&&(r_shadows.GetBool())) {
			backEnd.currentScissor = vLight->scissorRect;

			if (r_useScissor.GetBool()) {
				qglScissor(backEnd.viewDef->viewport.x1 + backEnd.currentScissor.x1,
				          backEnd.viewDef->viewport.y1 + backEnd.currentScissor.y1,
				          backEnd.currentScissor.x2 + 1 - backEnd.currentScissor.x1,
				          backEnd.currentScissor.y2 + 1 - backEnd.currentScissor.y1);
			}
			qglClear(GL_STENCIL_BUFFER_BIT);
		} else {
			// no shadows, so no need to read or write the stencil buffer
			// we might in theory want to use GL_ALWAYS instead of disabling
			// completely, to satisfy the invarience rules
			if (r_shadows.GetBool())
			qglStencilFunc(GL_ALWAYS, 128, 255);
		}

#ifdef _SHADOW_MAPPING
		if(ShadowMapping && vLight->shadowLOD >= 0)
		{
            int	side, sideStop;

            if( vLight->parallel )
            {
                side = 0;
                //sideStop = r_shadowMapSplits.GetInteger() + 1;
				sideStop = 1;
            }
            else if( vLight->pointLight )
            {
                if( r_shadowMapSingleSide.GetInteger() != -1 )
                {
                    side = r_shadowMapSingleSide.GetInteger();
                    sideStop = side + 1;
                }
                else
                {
                    side = 0;
                    sideStop = 6;
                }
            }
            else
            {
                side = -1;
                sideStop = 0;
            }

			if(vLight->globalShadows || vLight->localShadows)
			{
                qglDisable(GL_STENCIL_TEST);

				for( int m = side; m < sideStop ; m++ )
				{
					RB_ShadowMapPass( vLight->globalShadows, m, true );
				}

				for( int m = side; m < sideStop ; m++ )
				{
					RB_ShadowMapPass( vLight->localShadows, m, false );
				}

#ifdef _CONTROL_SHADOW_MAPPING_RENDERING
				if(PureShadowMapping)
				{
#endif
					RB_GLSL_CreateDrawInteractions_shadowMapping(vLight->localInteractions);
					RB_GLSL_CreateDrawInteractions_shadowMapping(vLight->globalInteractions);

					qglEnable(GL_STENCIL_TEST);
#ifdef _CONTROL_SHADOW_MAPPING_RENDERING
				}
				else
				{
					qglEnable(GL_STENCIL_TEST);

					RB_StencilShadowPass_shadowMapping(vLight->globalShadows);
					RB_GLSL_CreateDrawInteractions_shadowMapping(vLight->localInteractions);
					RB_StencilShadowPass_shadowMapping(vLight->localShadows);
					RB_GLSL_CreateDrawInteractions_shadowMapping(vLight->globalInteractions);
				}
#endif
			}
			else
			{
				RB_GLSL_CreateDrawInteractions(vLight->localInteractions);
				RB_GLSL_CreateDrawInteractions(vLight->globalInteractions);
			}
		}
		else
#endif
		{
            RB_StencilShadowPass(vLight->globalShadows);
#ifdef _TRANSLUCENT_STENCIL_SHADOW
			if(TranslucentStencilShadow)
			{
				RB_GLSL_CreateDrawInteractions_translucentStencilShadow(vLight->localInteractions, true);
				if(r_stencilShadowAlpha < 1.0f)
					RB_GLSL_CreateDrawInteractions_translucentStencilShadow(vLight->localInteractions, false);
			}
			else
#endif
			RB_GLSL_CreateDrawInteractions(vLight->localInteractions);

			RB_StencilShadowPass(vLight->localShadows);
#ifdef _TRANSLUCENT_STENCIL_SHADOW
			if(TranslucentStencilShadow)
			{
				RB_GLSL_CreateDrawInteractions_translucentStencilShadow(vLight->globalInteractions, true);
				if(r_stencilShadowAlpha < 1.0f)
					RB_GLSL_CreateDrawInteractions_translucentStencilShadow(vLight->globalInteractions, false);
			}
			else
#endif
			RB_GLSL_CreateDrawInteractions(vLight->globalInteractions);
		}

		//k GL_UseProgram(NULL);	// if there weren't any globalInteractions, it would have stayed on
		// translucent surfaces never get stencil shadowed
		if (r_skipTranslucent.GetBool()) {
			continue;
		}
		if (r_shadows.GetBool())
		qglStencilFunc(GL_ALWAYS, 128, 255);

		backEnd.depthFunc = GLS_DEPTHFUNC_LESS;
		RB_GLSL_CreateDrawInteractions(vLight->translucentInteractions);

		backEnd.depthFunc = GLS_DEPTHFUNC_EQUAL;
	}

	// disable stencil shadow test
	if (r_shadows.GetBool())
	qglStencilFunc(GL_ALWAYS, 128, 255);

	//GL_SelectTexture(0); //k2023
#ifdef _SHADOW_MAPPING
	if(ShadowMapping)
	{
		qglClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	}
    r_dumpShadowMap = false;
#endif
}

//===================================================================================

