void mg_mqtt_unsub(struct mg_connection *c, const struct mg_mqtt_opts *opts) {
  uint8_t qos_ = opts->qos & 3;
  size_t plen = c->is_mqtt5 ? get_props_size(opts->props, opts->num_props) : 0;
  size_t len = 2 + opts->topic.len + 2 + 1 + plen;
  mg_mqtt_send_header(c, MQTT_CMD_UNSUBSCRIBE, 2, (uint32_t) len);
  if (++c->mgr->mqtt_id == 0) ++c->mgr->mqtt_id;
  mg_send_u16(c, mg_htons(c->mgr->mqtt_id));
  if (c->is_mqtt5) mg_send_mqtt_properties(c, opts->props, opts->num_props);

  mg_send_u16(c, mg_htons((uint16_t) opts->topic.len));
  mg_send(c, opts->topic.ptr, opts->topic.len);
}