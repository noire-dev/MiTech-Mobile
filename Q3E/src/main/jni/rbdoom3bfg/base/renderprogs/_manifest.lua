return
{
	-- includes
	"global.inc.hlsl",
	"skinning.inc.hlsl",
	"builtin/post/SMAA.inc.hlsl",
	"BRDF.inc.hlsl",
	
	-- shaders
	"builtin/debug/debug_shadowmap.ps.hlsl",
	"builtin/debug/debug_shadowmap.vs.hlsl",
	"builtin/debug/shadowDebug.ps.hlsl",
	"builtin/debug/shadowDebug.vs.hlsl",
	"builtin/debug/shadowDebug_skinned.ps.hlsl",
	"builtin/debug/shadowDebug_skinned.vs.hlsl",
	"builtin/debug/octahedron.ps.hlsl",
	"builtin/debug/octahedron.vs.hlsl",
	"builtin/debug/lightgrid.ps.hlsl",
	"builtin/debug/lightgrid.vs.hlsl",
	
	"builtin/fog/blendLight.ps.hlsl",
	"builtin/fog/blendLight.vs.hlsl",
	"builtin/fog/fog.ps.hlsl",
	"builtin/fog/fog.vs.hlsl",
	"builtin/fog/fog_skinned.ps.hlsl",
	"builtin/fog/fog_skinned.vs.hlsl",
	
	"builtin/legacy/bumpyenvironment.ps.hlsl",
	"builtin/legacy/bumpyenvironment.vs.hlsl",
	"builtin/legacy/bumpyenvironment_skinned.ps.hlsl",
	"builtin/legacy/bumpyenvironment_skinned.vs.hlsl",
	"builtin/legacy/environment.ps.hlsl",
	"builtin/legacy/environment.vs.hlsl",
	"builtin/legacy/environment_skinned.ps.hlsl",
	"builtin/legacy/environment_skinned.vs.hlsl",
	"builtin/legacy/skybox.ps.hlsl",
	"builtin/legacy/skybox.vs.hlsl",
	"builtin/legacy/wobblesky.ps.hlsl",
	"builtin/legacy/wobblesky.vs.hlsl",
	
	"builtin/lighting/ambient_lighting.ps.hlsl",
	"builtin/lighting/ambient_lighting.vs.hlsl",
	"builtin/lighting/ambient_lighting_IBL.ps.hlsl",
	"builtin/lighting/ambient_lighting_IBL.vs.hlsl",
	"builtin/lighting/ambient_lightgrid_IBL.ps.hlsl",
	"builtin/lighting/ambient_lightgrid_IBL.vs.hlsl",
	"builtin/lighting/interaction.ps.hlsl",
	"builtin/lighting/interaction.vs.hlsl",
	"builtin/lighting/interactionAmbient.ps.hlsl",
	"builtin/lighting/interactionAmbient.vs.hlsl",
	"builtin/lighting/interactionAmbient_skinned.ps.hlsl",
	"builtin/lighting/interactionAmbient_skinned.vs.hlsl",
	"builtin/lighting/interactionSM.ps.hlsl",
	"builtin/lighting/interactionSM.vs.hlsl",
	"builtin/lighting/shadow.ps.hlsl",
	"builtin/lighting/shadow.vs.hlsl",
	"builtin/lighting/shadow_skinned.ps.hlsl",
	"builtin/lighting/shadow_skinned.vs.hlsl",
	
	"builtin/post/fxaa.ps.hlsl",
	"builtin/post/fxaa.vs.hlsl",
	"builtin/post/hdr_glare_chromatic.ps.hlsl",
	"builtin/post/hdr_glare_chromatic.vs.hlsl",
	"builtin/post/motionBlur.ps.hlsl",
	"builtin/post/motionBlur.vs.hlsl",
	"builtin/post/postprocess.ps.hlsl",
	"builtin/post/postprocess.vs.hlsl",
	"builtin/post/screen.ps.hlsl",
	"builtin/post/screen.vs.hlsl",
	"builtin/post/SMAA_blending_weight_calc.ps.hlsl",
	"builtin/post/SMAA_blending_weight_calc.vs.hlsl",
	"builtin/post/SMAA_edge_detection.ps.hlsl",
	"builtin/post/SMAA_edge_detection.vs.hlsl",
	"builtin/post/SMAA_final.ps.hlsl",
	"builtin/post/SMAA_final.vs.hlsl",
	"builtin/post/tonemap.ps.hlsl",
	"builtin/post/tonemap.vs.hlsl",
	
	"builtin/SSAO/AmbientOcclusion_AO.ps.hlsl",
	"builtin/SSAO/AmbientOcclusion_AO.vs.hlsl",
	"builtin/SSAO/AmbientOcclusion_blur.ps.hlsl",
	"builtin/SSAO/AmbientOcclusion_blur.vs.hlsl",
	"builtin/SSAO/AmbientOcclusion_minify.ps.hlsl",
	"builtin/SSAO/AmbientOcclusion_minify.vs.hlsl",
	
	"builtin/SSGI/DeepGBufferRadiosity_radiosity.ps.hlsl",
	"builtin/SSGI/DeepGBufferRadiosity_radiosity.vs.hlsl",
	"builtin/SSGI/DeepGBufferRadiosity_blur.ps.hlsl",
	"builtin/SSGI/DeepGBufferRadiosity_blur.vs.hlsl",
	
	"builtin/video/bink.ps.hlsl",
	"builtin/video/bink.vs.hlsl",
	"builtin/video/bink_gui.ps.hlsl",
	"builtin/video/bink_gui.vs.hlsl",
	
	"builtin/VR/stereoDeGhost.ps.hlsl",
	"builtin/VR/stereoDeGhost.vs.hlsl",
	"builtin/VR/stereoInterlace.ps.hlsl",
	"builtin/VR/stereoInterlace.vs.hlsl",
	"builtin/VR/stereoWarp.ps.hlsl",
	"builtin/VR/stereoWarp.vs.hlsl",
	
	"builtin/color.ps.hlsl",
	"builtin/color.vs.hlsl",
	
	"builtin/depth.ps.hlsl",
	"builtin/depth.vs.hlsl",
	"builtin/depth_skinned.ps.hlsl",
	"builtin/depth_skinned.vs.hlsl",
	
	"builtin/gbuffer.ps.hlsl",
	"builtin/gbuffer.vs.hlsl",
	"builtin/gui.ps.hlsl",
	"builtin/gui.vs.hlsl",
	
	"builtin/texture.ps.hlsl",
	"builtin/texture.vs.hlsl",
	"builtin/texture_color.ps.hlsl",
	"builtin/texture_color.vs.hlsl",
	"builtin/texture_color_skinned.ps.hlsl",
	"builtin/texture_color_skinned.vs.hlsl",
	"builtin/texture_color_texgen.ps.hlsl",
	"builtin/texture_color_texgen.vs.hlsl",
	
	"builtin/vertex_color.ps.hlsl",
	"builtin/vertex_color.vs.hlsl",
	
	-- optional shaders required by game materials
	"bloodorb1_capture.ps.hlsl",
	"bloodorb1_capture.vs.hlsl",
	"bloodorb2_capture.ps.hlsl",
	"bloodorb2_capture.vs.hlsl",
	"bloodorb3_capture.ps.hlsl",
	"bloodorb3_capture.vs.hlsl",
	"bloodorb_draw.ps.hlsl",
	"bloodorb_draw.vs.hlsl",
	"colorProcess.ps.hlsl",
	"colorProcess.vs.hlsl",
	"enviroSuit.ps.hlsl",
	"enviroSuit.vs.hlsl",
	"heatHazeWithMask.ps.hlsl",
	"heatHazeWithMask.vs.hlsl",
	"heatHazeWithMaskAndVertex.ps.hlsl",
	"heatHazeWithMaskAndVertex.vs.hlsl",
	"heathaze.ps.hlsl",
	"heathaze.vs.hlsl",
}

	
