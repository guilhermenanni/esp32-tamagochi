import { Button, StyleSheet } from "react-native";

export const style = StyleSheet.create({
    container:{
        flex:1,
        alignContent:'center',
        alignItems:'center'

    },

    top:{
        alignContent:'center',
        alignItems:'center',
        position:'absolute'

    },

    topText:{
        fontFamily:'sans-serif-bold',
        fontSize: 30,
        color:'black',
        marginTop: 40,
        marginBottom: 40
    },

    bottomStatusBar:{
        position: 'absolute',
        bottom: 0,
        backgroundColor:'#d3d3d3',
        width: '100%',
        alignContent:'center',
        alignItems:'center',
        height: 90,
    },

    bottomText:{},

    buttons:{
        alignContent:'center',
        alignItems:'center'
    },
})