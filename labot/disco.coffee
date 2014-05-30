# Description:
#   Trigger the discobot
#
# Dependencies:
#   None
#
# Configuration:
#   None
#
# Commands:
#   discobotapi <api url> - Set the discobot api url
#   alom - trigger the discobot
#
# Author:
#   steeeve

class Discobot
    constructor: (@robot) ->
        @robot.brain.on 'loaded', =>
            @cache = @robot.brain.data.discobot || {}

    save: ->
        @robot.brain.data.discobot = @cache

    setApi: (api) ->
        @cache.api = api
        @save()

    sendMode: (mode, callback) ->
        @robot.http(@cache.api)
            .query({
                mode: mode
            })
            .get() (err, res, body) ->
                callback(err, res, body)

module.exports = (robot) ->

    discobot = new Discobot robot

    robot.respond /discoapi (.*)/i, (msg) ->
        api = msg.match[1]
        if api && api != ''
            discobot.setApi api
        msg.send 'Discobot API set to: ' + api

    robot.hear /(^|\s+)alom(\s+|$)/i, (msg) ->
        discobot.sendMode 'd', (err, res, body)->
            if err
                msg.send 'Adaptive Party Interface not available :-('
            else
                msg.send 'Disco! :tada:'
